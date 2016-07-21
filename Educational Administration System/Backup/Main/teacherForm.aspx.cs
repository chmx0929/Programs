using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BLL;
using Model;
using System.Data;
using System.Data.SqlClient;

namespace Main
{
    public partial class TeacherForm : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            User u = new User();
            u = (User)Session["user"];
            Teacher t = new Teacher();
            t.Id = u.Id;
            
            if (!IsPostBack) 
            {
                SqlDataReader sdr = new teacher().selectCourseByTeacher(t);
                DropDownList1.Items.Add(new ListItem("未选择","null"));
                DropDownList2.Items.Add(new ListItem("未选择","null"));
                if (sdr.HasRows != false)
                while (sdr.Read())
                {
                    DropDownList1.Items.Add(new ListItem((string)sdr["name"],(string)sdr["id"]));
                    DropDownList2.Items.Add(new ListItem((string)sdr["name"],(string)sdr["id"]));
                }
            }
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            MultiView1.ActiveViewIndex = 0;
            Button1.Attributes["class"] = "selectedbutton";
            Button2.Attributes["class"] = "button";
            Button3.Attributes["class"] = "button";
        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            MultiView1.ActiveViewIndex = 1;
            Button1.Attributes["class"] = "button";
            Button2.Attributes["class"] = "selectedbutton";
            Button3.Attributes["class"] = "button";
        }

        protected void Button3_Click(object sender, EventArgs e)
        {
            MultiView1.ActiveViewIndex = 2;
            Button1.Attributes["class"] = "button";
            Button2.Attributes["class"] = "button";
            Button3.Attributes["class"] = "selectedbutton";
        }

        protected void Button4_Click(object sender, EventArgs e)
        {
            User u = new User();
            u = (User)Session["user"];
            Teacher t = new Teacher();
            t.Id = u.Id;
            DataSet ds = new teacher().selectAllScores(t);
            this.GridView1.DataSource = ds;
            this.GridView1.DataBind();
        }

        protected void Button5_Click(object sender, EventArgs e)
        {
            Course c = new Course();
            c.Id = DropDownList1.SelectedItem.Value;
            DataTable dt = new teacher().selectScoresByCourse(c);
            this.GridView1.DataSource = dt;
            this.GridView1.DataBind();
        }

        protected void Button6_Click(object sender, EventArgs e)
        {
            new teacher().update(DropDownList2.SelectedItem.Value, DropDownList3.SelectedItem.Value, int.Parse(TextBox1.Text));
        }

        protected void Button7_Click(object sender, EventArgs e)
        {
            Label2.Text = Label3.Text = "";
            User u = new User();
            u = (User)Session["user"];
            Teacher t = new Teacher();
            t.Id = u.Id;
            t.Name = u.Name;
            t.Password = u.Password;
            if (TextBox2.Text != t.Password) Label2.Text = "密码输入错误";
            else if (TextBox3.Text != TextBox3.Text) Label3.Text = "密码输入不一致";
            else new teacher().changePassword(t,TextBox3.Text);
        }

        protected void DropDownList2_SelectedIndexChanged(object sender, EventArgs e)
        {
            DropDownList3.Items.Clear();
            Course c = new Course();
            c.Id = DropDownList2.SelectedItem.Value;
            SqlDataReader sdr = new teacher().selectStudentByCourse_ID(c);
            DropDownList3.Items.Add(new ListItem("未选择", "null"));
            if (sdr.HasRows != false)
                while (sdr.Read())
                {
                    DropDownList3.Items.Add(new ListItem((string)sdr["id"], (string)sdr["id"]));
                }
        }

        protected void DropDownList3_SelectedIndexChanged(object sender, EventArgs e)
        {

            Label1.Text = new teacher().selectNameById(DropDownList3.SelectedItem.Value);
        }

        
    }
}