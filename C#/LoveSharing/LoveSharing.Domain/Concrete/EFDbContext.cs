using LoveSharing.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LoveSharing.Domain.Concrete
{
    public class EFDbContext:DbContext
    {
        /// <summary>
        /// 用户
        /// </summary>
        public DbSet<Users> Users { get; set; }
        /// <summary>
        /// 评论
        /// </summary>
        public DbSet<Comments> Comments { get; set; }
        /// <summary>
        /// 消息
        /// </summary>
        public DbSet<News> News { get; set; }
        /// <summary>
        /// 关注的好友
        /// </summary>
        public DbSet<Friends> Friends { get; set; }

        public DbSet<ForgetPassword> ForgetPassword { get; set; }
    }
}
