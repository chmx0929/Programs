using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;
using BLL;
using Model;

namespace Main
{
    public partial class managerForm : System.Web.UI.Page
    {
        Manager m=new Manager();
        protected void Page_Load(object sender, EventArgs e)
        {
            //if (!IsPostBack) 
            //{
            //    SqlDataReader sdr = new manager().selectT();
            //    DropDownList2.Items.Add(new ListItem("未选择", "null"));
            //    if (sdr.HasRows != false)
            //        while (sdr.Read())
            //            DropDownList2.Items.Add(new ListItem(sdr["id"].ToString(), sdr["name"].ToString()));
            //    sdr = new manager().selectS();
            //    DropDownList3.Items.Add(new ListItem("未选择", "null"));
            //    if (sdr.HasRows != false)
            //        while (sdr.Read())
            //            DropDownList3.Items.Add(new ListItem(sdr["id"].ToString(), sdr["name"].ToString()));
            //}
        }

        protected void Button4_Click(object sender, EventArgs e)
        {
            DataTable dt = new manager().selectT(1);
            this.GridView1.DataSource = dt;
            this.GridView1.DataBind();
        }

        protected void Button5_Click(object sender, EventArgs e)
        {
            MultiView2.ActiveViewIndex = 0;
            Button5.Attributes["class"] = "selectedbutton";
            Button6.Attributes["class"] = "button";
            Button7.Attributes["class"] = "button";
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

        protected void Button6_Click(object sender, EventArgs e)
        {
            MultiView2.ActiveViewIndex = 1;
            Button5.Attributes["class"] = "button";
            Button6.Attributes["class"] = "selectedbutton";
            Button7.Attributes["class"] = "button";


            DropDownList1.Items.Clear();
            SqlDataReader sdr = new manager().selectT();
            DropDownList1.Items.Add(new ListItem("未选择", "null"));
            if (sdr.HasRows != false)
                while (sdr.Read())
                    DropDownList1.Items.Add(new ListItem(sdr["id"].ToString(), sdr["name"].ToString()));
        }

        protected void Button7_Click(object sender, EventArgs e)
        {
            MultiView2.ActiveViewIndex = 2;
            Button5.Attributes["class"] = "button";
            Button6.Attributes["class"] = "button";
            Button7.Attributes["class"] = "selectedbutton";


            DropDownList2.Items.Clear();
            SqlDataReader sdr = new manager().selectT();
            DropDownList2.Items.Add(new ListItem("未选择", "null"));
            if (sdr.HasRows != false)
                while (sdr.Read())
                    DropDownList2.Items.Add(new ListItem(sdr["id"].ToString(), sdr["name"].ToString()));
        }

        protected void Button9_Click(object sender, EventArgs e)
        {
            Label4.Text = Label5.Text = "";
            User u = new User();
            u = (User)Session["user"];
            Manager m = new Manager();
            m.Id = u.Id;
            m.Name = u.Name;
            m.Password = u.Password;
            if (TextBox5.Text != m.Password) Label4.Text = "密码输入错误";
            else if (TextBox6.Text != TextBox7.Text) Label5.Text = "密码输入不一致";
            else new manager().changePassword(m, TextBox6.Text);
        }

        protected void Button11_Click(object sender, EventArgs e)
        {
            MultiView3.ActiveViewIndex = 0;
            Button11.Attributes["class"] = "selectedbutton";
            Button12.Attributes["class"] = "button";
            Button13.Attributes["class"] = "button";
        }

        protected void Button12_Click(object sender, EventArgs e)
        {
            MultiView3.ActiveViewIndex = 1;
            Button11.Attributes["class"] = "button";
            Button12.Attributes["class"] = "selectedbutton";
            Button13.Attributes["class"] = "button";


            DropDownList4.Items.Clear();
            SqlDataReader sdr = new manager().selectS();
            DropDownList4.Items.Add(new ListItem("未选择", "null"));
            if (sdr.HasRows != false)
                while (sdr.Read())
                    DropDownList4.Items.Add(new ListItem(sdr["id"].ToString(), sdr["name"].ToString()));
        }

        protected void Button13_Click(object sender, EventArgs e)
        {
            MultiView3.ActiveViewIndex = 2;
            Button11.Attributes["class"] = "button";
            Button12.Attributes["class"] = "button";
            Button13.Attributes["class"] = "selectedbutton";

            DropDownList3.Items.Clear();
            SqlDataReader sdr = new manager().selectS();
            DropDownList3.Items.Add(new ListItem("未选择", "null"));
            if (sdr.HasRows != false)
                while (sdr.Read())
                    DropDownList3.Items.Add(new ListItem(sdr["id"].ToString(), sdr["name"].ToString()));
        }

        protected void Button8_Click(object sender, EventArgs e)
        {
            new manager().insertT(TextBox2.Text, TextBox3.Text, TextBox4.Text, "course");
        }

        protected void Button16_Click(object sender, EventArgs e)
        {
            new manager().insertS(TextBox1.Text, TextBox11.Text, TextBox12.Text);
        }

        protected void Button15_Click(object sender, EventArgs e)
        {
            new manager().updateT(DropDownList1.SelectedItem.Text, TextBox8.Text, TextBox9.Text, "course");
        }

        protected void Button10_Click(object sender, EventArgs e)
        {
            DataTable dt = new manager().selectS(1);
            this.GridView2.DataSource = dt;
            this.GridView2.DataBind();
        }

        protected void Button14_Click(object sender, EventArgs e)
        {
            new manager().deleteT(DropDownList2.SelectedItem.Text);
            DropDownList2.Items.Clear();
            SqlDataReader sdr = new manager().selectT();
            DropDownList2.Items.Add(new ListItem("未选择", "null"));
            if (sdr.HasRows != false)
                while (sdr.Read())
                    DropDownList2.Items.Add(new ListItem(sdr["id"].ToString(), sdr["name"].ToString()));
            Label1.Text = "";
        }

        protected void Button18_Click(object sender, EventArgs e)
        {
            new manager().deleteS(DropDownList3.SelectedItem.Text);
            DropDownList3.Items.Clear();
            SqlDataReader sdr = new manager().selectS();
            DropDownList3.Items.Add(new ListItem("未选择", "null"));
            if (sdr.HasRows != false)
                while (sdr.Read())
                    DropDownList3.Items.Add(new ListItem(sdr["id"].ToString(), sdr["name"].ToString()));
            Label2.Text = "";
        }

        protected void DropDownList2_SelectedIndexChanged(object sender, EventArgs e)
        {
            Label1.Text = DropDownList2.SelectedItem.Value;
        }

        protected void DropDownList3_SelectedIndexChanged(object sender, EventArgs e)
        {
            Label2.Text = DropDownList3.SelectedItem.Value;
        }

        protected void Button17_Click(object sender, EventArgs e)
        {
            new manager().updateS(DropDownList4.SelectedItem.Text, TextBox13.Text, TextBox14.Text);
        }
    }
}