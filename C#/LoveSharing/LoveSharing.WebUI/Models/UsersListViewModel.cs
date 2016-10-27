using LoveSharing.Domain.Entities;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace LoveSharing.WebUI.Models
{
    /// <summary>
    ///用户列表视图模型，用于封装控制器发送给视图的所有数据
    /// </summary>
    public class UsersListViewModel
    {
        public IEnumerable<Users> Users { get; set; }
        public PagingInfo PagingInfo { get; set; }
    }
}