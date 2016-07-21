using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BLL;
using Model;
using System.Data.SqlClient;
using System.Data;


using System.Data;

namespace Main
{
    public partial class StudentForm : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
       
        }
        protected void Button1_Click(object sender, EventArgs e)
        {
            //User u = new User();
            //u = (User)Session["user"];
            //s.Id = u.Id;
            //s.Password = u.Password;
            //TextBox1.Text = s.Id + "   " + s.Password;

            //Teacher t = new Teacher();
            //t.Id = "21";
            //DataSet ds = new teacher().selectAll(t);


            //DataView dv = new DataView();
            ////dv.Table = ds.Tables[0];
            //dv.Sort = "score asc";//成绩升序 desc 降序
            //GridView1.DataSource = dv;
            //this.GridView1.Rows.

            //this.GridView1.DataSource = ds;
            //this.GridView1.DataBind();


            Label4.Text = Label5.Text = "";
            User u = new User();
            u = (User)Session["user"];
            Student s = new Student();
            s.Id = u.Id;
            s.Name = u.Name;
            s.Password = u.Password;
            if (TextBox5.Text != s.Password) Label4.Text = "密码输入错误";
            else if (TextBox6.Text != TextBox7.Text) Label5.Text = "密码输入不一致";
            else new student().changePassword(s, TextBox6.Text);
        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            MultiView1.ActiveViewIndex = 0;
            Button2.Attributes["class"] = "selectedbutton";
            Button3.Attributes["class"] = "button";
            Button4.Attributes["class"] = "button";


            User u = new User();
            u = (User)Session["user"];
            Student s = new Student();
            s.Id = u.Id;
            s.Password = u.Password;
            DataTable dt = new student().selectScores(s);
            this.GridView1.DataSource = dt;
            this.GridView1.DataBind();
        }

        protected void Button3_Click(object sender, EventArgs e)
        {
            MultiView1.ActiveViewIndex = 1;
            Button2.Attributes["class"] = "button";
            Button3.Attributes["class"] = "selectedbutton";
            Button4.Attributes["class"] = "button";

            CheckBoxList1.Items.Clear();
            student s1 = new student();
            User u = new User();
            u = (User)Session["user"];
            Student s = new Student();
            s.Id = u.Id;
            s.Password = u.Password;
            SqlDataReader sdr = s1.showChoosableCourses(s);
            //CheckBoxList1.Items.Add(new ListItem("未选择", "null"));
            if (sdr.HasRows!=false)
                while (sdr.Read())
                    CheckBoxList1.Items.Add(new ListItem(sdr["name"].ToString(), sdr["id"].ToString()));
        }

        protected void Button4_Click(object sender, EventArgs e)
        {
            MultiView1.ActiveViewIndex = 2;
            Button2.Attributes["class"] = "button";
            Button3.Attributes["class"] = "button";
            Button4.Attributes["class"] = "selectedbutton";
        }

        protected void Button5_Click(object sender, EventArgs e)
        {
            User u = new User();
            u = (User)Session["user"];
            Student s = new Student();
            s.Id = u.Id;
            s.Password = u.Password;

            for (int i = 0; i < CheckBoxList1.Items.Count; i++)
            {
                if (CheckBoxList1.Items[i].Selected == true)
                {
                    Course c = new Course();
                    c.Id = CheckBoxList1.Items[i].Value;
                    c.Name = CheckBoxList1.Items[i].Text;
                    new student().chooseCourse(s, c);
                }
            } 
        }
    }
}