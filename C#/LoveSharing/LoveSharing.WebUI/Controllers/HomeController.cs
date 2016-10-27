using LoveSharing.Domain.Abstract;
using LoveSharing.WebUI.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace LoveSharing.WebUI.Controllers
{
    [Authorize]
    public class HomeController : Controller
    {
        // GET: /Home/
        private IUsersRepository userRepository;

        public HomeController(IUsersRepository usersRepository)
        {
            this.userRepository = usersRepository;
        }

        public ActionResult Index()
        {
            return View(new SendViewModel());
        }

        public ViewResult List()
        {
            return View(userRepository.Users);
        }

        public ActionResult Search(string userName)
        {
            var user = from u in userRepository.Users.ToList()
                       where u.User_name.Equals(userName)
                       select u;
            return View(user);
        }

        [Authorize]
        [HttpPost]
        public ActionResult Send()
        {
            return RedirectToAction("Index", "Home");
        }

    }
}
