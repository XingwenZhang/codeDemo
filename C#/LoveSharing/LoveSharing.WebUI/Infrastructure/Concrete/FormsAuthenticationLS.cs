using LoveSharing.WebUI.Models;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Web;

namespace LoveSharing.WebUI.Infrastructure.Concrete
{
    public sealed class FormsAuthenticationLS
    {
        public static bool Authenticate(string email, string password)
        {
            string sql = "select count(*) from Users where email=@email and password=@password";
            SqlParameter[] parameters = new SqlParameter[]
            {
                new SqlParameter("email",email),
                new SqlParameter("password",password)
            };
            if ((int)SqlHelper.ExecuteScalar(sql,parameters) > 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    }
}