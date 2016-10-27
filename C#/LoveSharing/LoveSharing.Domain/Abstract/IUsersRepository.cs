using LoveSharing.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LoveSharing.Domain.Abstract
{
    public interface IUsersRepository
    {
        /// <summary>
        /// 获取一系列Users对象
        /// </summary>
        IQueryable<Users> Users { get; }
        void SaveUser(Users user);
        void SavePassword(Int64 id, string oldpsd, string newpsd, string confirmpsd);
    }
}
