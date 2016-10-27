using LoveSharing.WebUI.Infrastructure.Abstract;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;

namespace LoveSharing.WebUI.Infrastructure.Concrete
{
    public class FormsAuthProvider:IAuthProvider
    {

        public bool Authenticate(string email, string password)
        {
            bool result = FormsAuthenticationLS.Authenticate(email, password);
            if (result)
            {
                FormsAuthentication.SetAuthCookie(email, false);
            }
            return result;
        }
    }
}