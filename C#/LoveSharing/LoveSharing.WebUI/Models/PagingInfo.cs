using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace LoveSharing.WebUI.Models
{
    /// <summary>
    /// 用于分页的视图模型
    /// </summary>
    public class PagingInfo
    {
        /// <summary>
        /// 总的条目数
        /// </summary>
        public int TotalItems { get; set; }
        /// <summary>
        /// 每页的条目数
        /// </summary>
        public int ItemsPerPage { get; set; }
        /// <summary>
        /// 当前页号
        /// </summary>
        public int CurrentPage { get; set; }
        /// <summary>
        /// 总的页数
        /// </summary>
        public int TotalPages
        {
            get { return (int)Math.Ceiling((decimal)TotalItems / ItemsPerPage); }
        }
    }
}