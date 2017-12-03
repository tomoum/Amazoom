namespace Managers_GUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.check_quantity_btn = new System.Windows.Forms.Button();
            this.shutdown_btn = new System.Windows.Forms.Button();
            this.launch_btn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.product_query_cbox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.order_ID_cbox = new System.Windows.Forms.ComboBox();
            this.product_quantity_tb = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.order_status_tb = new System.Windows.Forms.TextBox();
            this.check_order_btn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // check_quantity_btn
            // 
            this.check_quantity_btn.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.check_quantity_btn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.check_quantity_btn.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.check_quantity_btn.Location = new System.Drawing.Point(929, 114);
            this.check_quantity_btn.Margin = new System.Windows.Forms.Padding(4);
            this.check_quantity_btn.Name = "check_quantity_btn";
            this.check_quantity_btn.Size = new System.Drawing.Size(407, 51);
            this.check_quantity_btn.TabIndex = 1;
            this.check_quantity_btn.Text = "Check Available Quantity";
            this.check_quantity_btn.UseVisualStyleBackColor = false;
            // 
            // shutdown_btn
            // 
            this.shutdown_btn.BackColor = System.Drawing.Color.LightCoral;
            this.shutdown_btn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.shutdown_btn.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.shutdown_btn.Location = new System.Drawing.Point(53, 609);
            this.shutdown_btn.Margin = new System.Windows.Forms.Padding(4);
            this.shutdown_btn.Name = "shutdown_btn";
            this.shutdown_btn.Size = new System.Drawing.Size(379, 99);
            this.shutdown_btn.TabIndex = 2;
            this.shutdown_btn.Text = "System Shutdown";
            this.shutdown_btn.UseVisualStyleBackColor = false;
            // 
            // launch_btn
            // 
            this.launch_btn.BackColor = System.Drawing.Color.MediumAquamarine;
            this.launch_btn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.launch_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.launch_btn.Location = new System.Drawing.Point(53, 477);
            this.launch_btn.Margin = new System.Windows.Forms.Padding(4);
            this.launch_btn.Name = "launch_btn";
            this.launch_btn.Size = new System.Drawing.Size(379, 99);
            this.launch_btn.TabIndex = 3;
            this.launch_btn.Text = "Launch Warehouse";
            this.launch_btn.UseVisualStyleBackColor = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Arial", 13.875F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(45, 402);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(328, 44);
            this.label1.TabIndex = 4;
            this.label1.Text = "System Controls:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(47, 726);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(683, 31);
            this.label2.TabIndex = 5;
            this.label2.Text = "Warning! complete shutdown of all warehouse systems.";
            // 
            // product_query_cbox
            // 
            this.product_query_cbox.FormattingEnabled = true;
            this.product_query_cbox.Location = new System.Drawing.Point(317, 121);
            this.product_query_cbox.Name = "product_query_cbox";
            this.product_query_cbox.Size = new System.Drawing.Size(567, 39);
            this.product_query_cbox.TabIndex = 8;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(187, 220);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(0, 31);
            this.label3.TabIndex = 10;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(47, 124);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(124, 36);
            this.label4.TabIndex = 11;
            this.label4.Text = "Product";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Arial", 13.875F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(45, 50);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(196, 44);
            this.label5.TabIndex = 12;
            this.label5.Text = "Inventory ";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(47, 260);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(137, 36);
            this.label6.TabIndex = 13;
            this.label6.Text = "Order ID";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // order_ID_cbox
            // 
            this.order_ID_cbox.FormattingEnabled = true;
            this.order_ID_cbox.Location = new System.Drawing.Point(317, 260);
            this.order_ID_cbox.Name = "order_ID_cbox";
            this.order_ID_cbox.Size = new System.Drawing.Size(567, 39);
            this.order_ID_cbox.TabIndex = 14;
            // 
            // product_quantity_tb
            // 
            this.product_quantity_tb.Location = new System.Drawing.Point(317, 194);
            this.product_quantity_tb.Name = "product_quantity_tb";
            this.product_quantity_tb.Size = new System.Drawing.Size(413, 38);
            this.product_quantity_tb.TabIndex = 15;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(47, 194);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(133, 36);
            this.label7.TabIndex = 16;
            this.label7.Text = "Quantity";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(47, 324);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(105, 36);
            this.label8.TabIndex = 17;
            this.label8.Text = "Status";
            // 
            // order_status_tb
            // 
            this.order_status_tb.Location = new System.Drawing.Point(317, 337);
            this.order_status_tb.Name = "order_status_tb";
            this.order_status_tb.Size = new System.Drawing.Size(413, 38);
            this.order_status_tb.TabIndex = 18;
            // 
            // check_order_btn
            // 
            this.check_order_btn.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.check_order_btn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.check_order_btn.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.check_order_btn.Location = new System.Drawing.Point(929, 260);
            this.check_order_btn.Margin = new System.Windows.Forms.Padding(4);
            this.check_order_btn.Name = "check_order_btn";
            this.check_order_btn.Size = new System.Drawing.Size(407, 51);
            this.check_order_btn.TabIndex = 1;
            this.check_order_btn.Text = "Check Status";
            this.check_order_btn.UseVisualStyleBackColor = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1365, 775);
            this.Controls.Add(this.check_order_btn);
            this.Controls.Add(this.order_status_tb);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.product_quantity_tb);
            this.Controls.Add(this.order_ID_cbox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.product_query_cbox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.launch_btn);
            this.Controls.Add(this.shutdown_btn);
            this.Controls.Add(this.check_quantity_btn);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Managers UI";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button check_quantity_btn;
        private System.Windows.Forms.Button shutdown_btn;
        private System.Windows.Forms.Button launch_btn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox product_query_cbox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox order_ID_cbox;
        private System.Windows.Forms.TextBox product_quantity_tb;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox order_status_tb;
        private System.Windows.Forms.Button check_order_btn;
    }
}

