using LoveSharing.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.Providers.Entities;

namespace LoveSharing.WebUI.Models.Helpers
{
    public static class UserHandler
    {
        public static void CreateUserAndAccountByEmail(string userName,string email,string password)
        {
            string sql = "insert into Users(user_name,email,password) values(@userName,@email,@password)";
            SqlParameter[] parameters = new SqlParameter[]
            {
                new SqlParameter("@userName",userName),
                new SqlParameter("@email",email),
                new SqlParameter("@password",password)
            };
            SqlHelper.ExecuteNonQuery(sql, parameters);
        }

        public static Int64 GetUserIdByEmail(string email)
        {
            string sql = "select user_id from users where email=@email";
            return (Int64)SqlHelper.ExecuteScalar(sql, new SqlParameter("@email", email));
        }

        public static string GetUserNameByEmail(string email)
        {
            string sql = "select user_name from users where email=@email";
            return (string)SqlHelper.ExecuteScalar(sql, new SqlParameter("@email", email));
        }

        public static bool IsRepeatedUserName(string userName)
        {
            string sql = "select count(*) from users where user_name = @userName";
            if ((int)SqlHelper.ExecuteScalar(sql,new SqlParameter("@userName",userName)) > 0)
            {
                return true;
            }

            return false;
        }

        public static bool IsRepeatedEmail(string email)
        {
            string sql = "select email from users where email = @email";
            if (SqlHelper.ExecuteNonQuery(sql, new SqlParameter("@email", email)) > 0)
            {
                return true;
            }

            return false;
        }

        public static bool IsMyFriend(Int64 my_id,Int64 id)
        {
            string sql = "select count(*) from friends where my_id = @my_id and friend_id = @id";
            SqlParameter[] parameters = new SqlParameter[]
            {
                new SqlParameter("@my_id",my_id),
                new SqlParameter("@id",id)
            };
            if((int)SqlHelper.ExecuteScalar(sql,parameters) > 0)
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