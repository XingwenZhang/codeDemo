using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using LoveSharing.WebUI.Models.Helpers;
using LoveSharing.Domain.Abstract;
using LoveSharing.Domain.Entities;
using LoveSharing.WebUI.Infrastructure.Abstract;
using LoveSharing.WebUI.Models;
using System.Data.SqlClient;

namespace LoveSharing.WebUI.Controllers
{
    public class ForgetPasswordController : Controller
    {
        private IEmailProcessor emailProcessor;
        private IUsersRepository userRepository;
        private IForgetPasswordRepository forgetPasswordRepository;
        //
        // GET: /ForgetPassword/
        public ForgetPasswordController(IEmailProcessor email,IUsersRepository userrepo,
            IForgetPasswordRepository forgetpsd)
        {
            emailProcessor=email;
            userRepository=userrepo;
            forgetPasswordRepository = forgetpsd;
        }
        
        public ViewResult ForgetPassword()
        {
            return View();
        }
        [HttpPost]
        public ActionResult ForgetPassword(string Email)
        {
            //Int64 id = UserHandler.GetUserIdByEmail(User.Identity.Name);

            Users user = userRepository.Users.FirstOrDefault(x => x.Email==Email);
            Int64 id = user.User_id;
            if (user != null)
            {
                InsertForgetRecord(id,Email);
            }
            //发送邮件
            ForgetPassword forgetPsd = forgetPasswordRepository.ForgetPassword.FirstOrDefault(p => p.User_id == id);
            //emailProcessor.ProcessPassword();
            
            emailProcessor.ProcessPassword(forgetPsd);

            return RedirectToAction("Login", "Account");
        }

        public ViewResult ChangePassword2()
        {
            return View();
        }
        [HttpPost]
        public ActionResult ChangePassword2(int Forget_id,string newPassword,string confirmPassword)
        {
            //Int64 id = UserHandler.GetUserIdByEmail(User.Identity.Name);
            //userRepository.SavePassword(id, OldPassword, NewPassword, ConfirmPassword);
            //return RedirectToAction("../Home/Index");
            forgetPasswordRepository.SaveForgetPassword(Forget_id, newPassword, confirmPassword);

            return RedirectToAction("Login", "Account");
        }

        [HttpGet]
        public ActionResult ChangePassword(string token,string id)
        {
            int tempid = int.Parse(id);
            ForgetPassword forgetPsd= forgetPasswordRepository.ForgetPassword.FirstOrDefault(x => x.Forget_id == tempid);
            if(forgetPsd.random_md5.Equals(token))
                if((DateTime.Parse(forgetPsd.expiration_time).CompareTo(DateTime.Parse(DateTime.Now.ToString())))>0)
                {
                    return RedirectToAction("ChangePassword2", new {Forget_id = id });
                }
                else
                {
                    return RedirectToAction("error");
                }
            else
            {
                return RedirectToAction("error");
            }
        }

        public void InsertForgetRecord(Int64 user_id,string Email)
        {
            DeleteForgetRecord(user_id);
            string rand_md5 = DateTime.Now.GetHashCode().ToString();
            string exp_time = DateTime.Now.AddMinutes(20).ToString();
            string sql = "Insert into ForgetPasswords(User_id,expiration_time,random_md5) values(@user_id,@exp_time,@md5)";
            SqlParameter[] parameters = new SqlParameter[]
            {
                new SqlParameter("@user_id",user_id),
                new SqlParameter("@exp_time",exp_time),
                new SqlParameter("@md5",rand_md5)
            };
            SqlHelper.ExecuteNonQuery(sql, parameters);
        }
        public void DeleteForgetRecord(Int64 user_id)
        {
            string sql = "delete from ForgetPasswords where User_id = @user_id";
            SqlParameter[] parameters = new SqlParameter[]
            {
                new SqlParameter("@user_id",user_id)
            };
            SqlHelper.ExecuteNonQuery(sql, parameters);
        }



    }
}
