using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BLL;
using Model;

namespace Main
{
    public partial class Login : System.Web.UI.Page
    {

        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void submit_Click(object sender, EventArgs e)
        {
            User u = new User();
            u.Id = ID.Text;
            u.Password = Password.Text;
            u.Identity = identity.SelectedValue;
            u=new user().check(u);
            if ( u!= null)
            {
                Session["user"] = u;
                Response.Redirect(u.Identity+"Form.aspx");
            }
            else
            {
                ClientScript.RegisterStartupScript(this.GetType(), "", "<script>alert('用户名、密码不正确！');</script>");
            }
        }
    }
}