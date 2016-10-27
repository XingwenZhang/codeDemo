using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Web.Mvc;
using LoveSharing.WebUI.Models;
using LoveSharing.WebUI.HtmlHelpers;

namespace LoveSharing.UnitTests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void Can_Generate_Page_Links()
        {
            HtmlHelper myHelper = null;

            PagingInfo pagingInfo = new PagingInfo
            {
                CurrentPage = 2,
                TotalItems = 28,
                ItemsPerPage = 10
            };

            Func<int, string> pageUrlDelegate = i => "Page" + i;

            MvcHtmlString result = myHelper.PageLinks(pagingInfo, pageUrlDelegate);



            //class 后面加个空格都会测试失败
            Assert.AreEqual(result.ToString(),@"<a href=""Page1"">1</a>" + @"<a class=""selected"" href=""Page2"">2</a>" + @"<a href=""Page3"">3</a>");
        }
    }
}
