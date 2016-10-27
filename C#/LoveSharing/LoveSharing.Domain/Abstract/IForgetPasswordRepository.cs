using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LoveSharing.Domain.Entities;

namespace LoveSharing.Domain.Abstract
{
    public interface IForgetPasswordRepository
    {
        IQueryable<ForgetPassword> ForgetPassword { get; }
        void SaveForgetPassword(int forget_id,string newpsd, string confirmpsd);
    }
}
