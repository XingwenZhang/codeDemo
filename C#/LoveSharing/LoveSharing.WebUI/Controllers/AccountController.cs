using LoveSharing.Domain.Abstract;
using LoveSharing.Domain.Entities;
using LoveSharing.WebUI.Infrastructure.Abstract;
using LoveSharing.WebUI.Models;
using LoveSharing.WebUI.Models.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Security;



namespace LoveSharing.WebUI.Controllers
{
    public class AccountController : Controller
    {
        private IUsersRepository userRepository;
        private IFriendsRepository friendsRepository;
        private IAuthProvider authProvider;   //授权接口
        public int PageSize = 10;             //页大小

        // GET: /Account/
        public AccountController(IUsersRepository userRepo,IFriendsRepository friendRepo,IAuthProvider auth)
        {
            this.userRepository = userRepo;
            this.friendsRepository = friendRepo;
            this.authProvider = auth;
        }

        //Get: /Account/Register
        [AllowAnonymous]
        public ViewResult Register()
        {
            return View();
        }

        //Post: /Account/Register
        [HttpPost]
        [AllowAnonymous]
        //[ValidateAntiForgeryToken]   //防止CSRF跨网站请求伪造
        public ActionResult Register(RegisterModel model)
        {
            try
            {
                if (UserHandler.IsRepeatedUserName(model.Name))
                {
                    return View();
                }
                if (UserHandler.IsRepeatedEmail(model.Email))
                {
                    return View();
                }
                UserHandler.CreateUserAndAccountByEmail(model.Name,model.Email,model.Password);
                return RedirectToAction("Login", "Account");
            }
            catch (Exception)
            {
                
                throw;
            }
        }


        [AllowAnonymous]
        public ViewResult Login()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Login(LoginModel model,string returnUrl)
        {
            if(ModelState.IsValid){
                if(authProvider.Authenticate(model.Email,model.Password))
                {
                    return Redirect(Url.Action("Index", "Home"));
                }
                else
                {
                    ModelState.AddModelError("", "错误的用户名和密码");
                    return View();
                }
            }
            else
            {
                return View();
            }
        }


        /// <summary>
        /// 注销
        /// </summary>
        /// <returns></returns>
        [HttpPost]
        public ActionResult LogOff()
        {
            FormsAuthentication.SignOut();

            return RedirectToAction("Login", "Account");
        }

        /// <summary>
        /// 列出所有关注我的好友
        /// </summary>
        /// <param name="page"></param>
        /// <returns></returns>
        [Authorize]
        public ViewResult ListFriends(int page = 1)
        {
           //通过我的Email获得我的ＩＤ
            Int64 my_id = UserHandler.GetUserIdByEmail(User.Identity.Name);

            //根据我的ＩＤ获得好友ＩＤ
            var f_ids = from f in friendsRepository.Friends.ToList()
                              where f.My_id == my_id
                              select f.Friend_id;

            //根据好友ＩＤ获得好友信息
            var friends = from u in userRepository.Users.ToList()
                    where f_ids.Contains(u.User_id)
                    select u;


            FriendsListViewModel model = new FriendsListViewModel
            {
                Friends = friends,
                PagingInfo = new PagingInfo
                {
                    CurrentPage = page,
                    ItemsPerPage = PageSize,
                    TotalItems = friendsRepository.Friends.Count()
                }
            };

            return View(model);
         }  
     
        /// <summary>
        /// 个人资料
        /// </summary>
        /// <returns></returns>
        [Authorize]
        public ViewResult PersonalInfo()
        {
            Int64 id = UserHandler.GetUserIdByEmail(User.Identity.Name);
            Users user = userRepository.Users.FirstOrDefault(x=>x.User_id==id);
            return View(user);
        }
        [HttpPost]
        public ActionResult PersonalInfo(Users user, HttpPostedFileBase Imagedata)
        {
            if (ModelState.IsValid)
            {
                if (Imagedata != null)
                {
                    user.ImageMineType = Imagedata.ContentType;
                    user.Image = new byte[Imagedata.ContentLength];
                    Imagedata.InputStream.Read(user.Image, 0, Imagedata.ContentLength);
                }
            }
            userRepository.SaveUser(user);
            TempData["message"] = string.Format("{0} has been saved", user.User_name);
            return RedirectToAction("../Home/Index");
        }

        public ViewResult Manage()
        {
            //string userEmail = (string)Session["userEmail"];
            //Users user = userRepository.Users.FirstOrDefault(x => x.Email == userEmail);
            //return View(user);
            LocalPasswordModel locPsd = new LocalPasswordModel();
            return View(locPsd);
        }
        //[Authorize]
        [HttpPost]
        public ActionResult Manage(string OldPassword, string NewPassword, string ConfirmPassword)
        {
            //string userEmail = (string)Session["userEmail"];

            Int64 id = UserHandler.GetUserIdByEmail(User.Identity.Name);
            userRepository.SavePassword(id, OldPassword, NewPassword, ConfirmPassword);
            return RedirectToAction("../Home/Index");
        }

        public FileContentResult GetImage(Int64 user_id)
        {
            Users user = userRepository.Users.FirstOrDefault(p => p.User_id == user_id);
            if (user != null)
            {
                return File(user.Image, user.ImageMineType);
            }
            else
            {
                return null;
            }
        }


        /// <summary>
        /// 列出好友详细信息
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize]
        public ViewResult Details(Int64 id)
        {
            var q = from u in userRepository.Users.ToList()
                    where u.User_id == id
                    select u;
            return View(q.FirstOrDefault() as Users);
        }

        [Authorize]
        public ActionResult Follow(bool flag,Int64 id,string userName)
        {
            Int64 my_id = UserHandler.GetUserIdByEmail(User.Identity.Name);
            if (flag == true)    //是好友，取消关注
            {
                FriendsHandler.CancelFollow(my_id, id);
            }
            else                 //不是好友，加好友
            {
                FriendsHandler.Follow(my_id, id);
            }
            return RedirectToAction("Search", "Home", new { userName = userName});
        }

        [Authorize]
        public ActionResult CancelFollow(bool flag, Int64 id, string userName)
        {
            Int64 my_id = UserHandler.GetUserIdByEmail(User.Identity.Name);

            FriendsHandler.CancelFollow(my_id, id);

            return RedirectToAction("ListFriends", "Account");
        }

    }
}
