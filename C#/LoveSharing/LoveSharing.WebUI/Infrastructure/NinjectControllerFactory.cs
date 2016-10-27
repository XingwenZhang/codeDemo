using LoveSharing.Domain.Abstract;
using LoveSharing.Domain.Concrete;
using LoveSharing.Domain.Entities;
using LoveSharing.WebUI.Infrastructure.Abstract;
using LoveSharing.WebUI.Infrastructure.Concrete;
using Moq;
using Ninject;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using System.Configuration;

namespace LoveSharing.WebUI.Infrastructure
{
    public class NinjectControllerFactory:DefaultControllerFactory
    {
        private IKernel ninjectKernel;

        public NinjectControllerFactory()
        {
            ninjectKernel = new StandardKernel();
            AddBindings();
        }

        protected override IController GetControllerInstance(RequestContext requestContext, Type controllerType)
        {
            return controllerType == null ? null : (IController)ninjectKernel.Get(controllerType);
        }

        private void AddBindings()
        {
            //put bindings here
            //Mock<IUsersRepository> mock = new Mock<IUsersRepository>();
            //mock.Setup(m => m.Users).Returns(new List<Users>
            //    {
            //        new Users{User_name = "Terry",Age = 23},
            //        new Users{User_name = "Jing_lee",Age = 20}
            //    }.AsQueryable());
            //ninjectKernel.Bind<IUsersRepository>().ToConstant(mock.Object);

            ninjectKernel.Bind<IUsersRepository>().To<EFUsersRepository>();
            ninjectKernel.Bind<IFriendsRepository>().To<EFFriendsRepository>();
            ninjectKernel.Bind<IAuthProvider>().To<FormsAuthProvider>();
            EmailSettings emailSettings = new EmailSettings
            {
                WriteAsFile = bool.Parse(ConfigurationManager.AppSettings["Email.WriteAsFile"] ?? "false")
            };
            ninjectKernel.Bind<IEmailProcessor>().To<EmailProcessor>()
                .WithConstructorArgument("settings", emailSettings);

            ninjectKernel.Bind<IForgetPasswordRepository>().To<EFForgetPasswordRepository>();
        }
    }
}