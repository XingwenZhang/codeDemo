using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LoveSharing.Domain.Entities;
namespace LoveSharing.Domain.Abstract
{
    public interface IEmailProcessor
    {
        void ProcessPassword(ForgetPassword forgPsd);
    }
}
