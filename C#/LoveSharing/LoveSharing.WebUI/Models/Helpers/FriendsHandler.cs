using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Web;

namespace LoveSharing.WebUI.Models.Helpers
{
    public static class FriendsHandler
    {
        public static bool CancelFollow(Int64 my_id,Int64 id)
        {
            string sql = "delete from friends where my_id=@my_id and friend_id = @id";
            SqlParameter[] parameters = new SqlParameter[]
            {
                new SqlParameter("@my_id",my_id),
                new SqlParameter("@id",id)
            };

            if (SqlHelper.ExecuteNonQuery(sql,parameters) > 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static bool Follow(Int64 my_id,Int64 id)
        {
            string sql = "insert into friends(my_id,friend_id) values(@my_id,@id)";
            SqlParameter[] parameters = new SqlParameter[]
            {
                new SqlParameter("@my_id",my_id),
                new SqlParameter("@id",id)
            };

            if (SqlHelper.ExecuteNonQuery(sql, parameters) > 0)
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