
namespace zumoAssignmentGUI
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
            this.ForwardButton = new System.Windows.Forms.Button();
            this.TurnRightButtonM = new System.Windows.Forms.Button();
            this.BackButton = new System.Windows.Forms.Button();
            this.TurnLeftButtonM = new System.Windows.Forms.Button();
            this.StopButton = new System.Windows.Forms.Button();
            this.ManualControlGroup = new System.Windows.Forms.GroupBox();
            this.AutonomousControlGroup = new System.Windows.Forms.GroupBox();
            this.RoomRightButton = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.RoomLeftButton = new System.Windows.Forms.Button();
            this.TurnLeftButtonA = new System.Windows.Forms.Button();
            this.TurnRightButtonA = new System.Windows.Forms.Button();
            this.SwitchControlButton = new System.Windows.Forms.Button();
            this.ManualControlGroup.SuspendLayout();
            this.AutonomousControlGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // ForwardButton
            // 
            this.ForwardButton.Location = new System.Drawing.Point(165, 17);
            this.ForwardButton.Name = "ForwardButton";
            this.ForwardButton.Size = new System.Drawing.Size(150, 75);
            this.ForwardButton.TabIndex = 0;
            this.ForwardButton.Text = "Forward";
            this.ForwardButton.UseVisualStyleBackColor = true;
            this.ForwardButton.Click += new System.EventHandler(this.ForwardButton_Click);
            // 
            // TurnRightButtonM
            // 
            this.TurnRightButtonM.Location = new System.Drawing.Point(321, 98);
            this.TurnRightButtonM.Name = "TurnRightButtonM";
            this.TurnRightButtonM.Size = new System.Drawing.Size(150, 75);
            this.TurnRightButtonM.TabIndex = 1;
            this.TurnRightButtonM.Text = "Turn Right";
            this.TurnRightButtonM.UseVisualStyleBackColor = true;
            this.TurnRightButtonM.Click += new System.EventHandler(this.TurnRightButton_Click);
            // 
            // BackButton
            // 
            this.BackButton.Location = new System.Drawing.Point(165, 179);
            this.BackButton.Name = "BackButton";
            this.BackButton.Size = new System.Drawing.Size(150, 75);
            this.BackButton.TabIndex = 2;
            this.BackButton.Text = "Back";
            this.BackButton.UseVisualStyleBackColor = true;
            this.BackButton.Click += new System.EventHandler(this.BackButton_Click);
            // 
            // TurnLeftButtonM
            // 
            this.TurnLeftButtonM.Location = new System.Drawing.Point(9, 98);
            this.TurnLeftButtonM.Name = "TurnLeftButtonM";
            this.TurnLeftButtonM.Size = new System.Drawing.Size(150, 75);
            this.TurnLeftButtonM.TabIndex = 3;
            this.TurnLeftButtonM.Text = "Turn Left";
            this.TurnLeftButtonM.UseVisualStyleBackColor = true;
            this.TurnLeftButtonM.Click += new System.EventHandler(this.TurnLeftButton_Click);
            // 
            // StopButton
            // 
            this.StopButton.Location = new System.Drawing.Point(165, 98);
            this.StopButton.Name = "StopButton";
            this.StopButton.Size = new System.Drawing.Size(150, 75);
            this.StopButton.TabIndex = 4;
            this.StopButton.Text = "Stop";
            this.StopButton.UseVisualStyleBackColor = true;
            this.StopButton.Click += new System.EventHandler(this.StopButton_Click);
            // 
            // ManualControlGroup
            // 
            this.ManualControlGroup.Controls.Add(this.StopButton);
            this.ManualControlGroup.Controls.Add(this.ForwardButton);
            this.ManualControlGroup.Controls.Add(this.TurnRightButtonM);
            this.ManualControlGroup.Controls.Add(this.TurnLeftButtonM);
            this.ManualControlGroup.Controls.Add(this.BackButton);
            this.ManualControlGroup.Location = new System.Drawing.Point(12, 12);
            this.ManualControlGroup.Name = "ManualControlGroup";
            this.ManualControlGroup.Size = new System.Drawing.Size(479, 265);
            this.ManualControlGroup.TabIndex = 7;
            this.ManualControlGroup.TabStop = false;
            this.ManualControlGroup.Text = "Manual Controls";
            // 
            // AutonomousControlGroup
            // 
            this.AutonomousControlGroup.Controls.Add(this.RoomRightButton);
            this.AutonomousControlGroup.Controls.Add(this.button1);
            this.AutonomousControlGroup.Controls.Add(this.RoomLeftButton);
            this.AutonomousControlGroup.Controls.Add(this.TurnLeftButtonA);
            this.AutonomousControlGroup.Controls.Add(this.TurnRightButtonA);
            this.AutonomousControlGroup.Location = new System.Drawing.Point(637, 12);
            this.AutonomousControlGroup.Name = "AutonomousControlGroup";
            this.AutonomousControlGroup.Size = new System.Drawing.Size(341, 265);
            this.AutonomousControlGroup.TabIndex = 8;
            this.AutonomousControlGroup.TabStop = false;
            this.AutonomousControlGroup.Text = "Autonomous Controls";
            // 
            // RoomRightButton
            // 
            this.RoomRightButton.Location = new System.Drawing.Point(174, 17);
            this.RoomRightButton.Name = "RoomRightButton";
            this.RoomRightButton.Size = new System.Drawing.Size(150, 75);
            this.RoomRightButton.TabIndex = 4;
            this.RoomRightButton.Text = "Room Right";
            this.RoomRightButton.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(100, 179);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(150, 75);
            this.button1.TabIndex = 4;
            this.button1.Text = "Start/Stop";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.StopButton_Click);
            // 
            // RoomLeftButton
            // 
            this.RoomLeftButton.Enabled = false;
            this.RoomLeftButton.Location = new System.Drawing.Point(18, 17);
            this.RoomLeftButton.Name = "RoomLeftButton";
            this.RoomLeftButton.Size = new System.Drawing.Size(150, 75);
            this.RoomLeftButton.TabIndex = 4;
            this.RoomLeftButton.Text = "Room Left";
            this.RoomLeftButton.UseVisualStyleBackColor = true;
            // 
            // TurnLeftButtonA
            // 
            this.TurnLeftButtonA.Location = new System.Drawing.Point(18, 98);
            this.TurnLeftButtonA.Name = "TurnLeftButtonA";
            this.TurnLeftButtonA.Size = new System.Drawing.Size(150, 75);
            this.TurnLeftButtonA.TabIndex = 3;
            this.TurnLeftButtonA.Text = "Turn Left";
            this.TurnLeftButtonA.UseVisualStyleBackColor = true;
            this.TurnLeftButtonA.Click += new System.EventHandler(this.TurnLeftButton_Click);
            // 
            // TurnRightButtonA
            // 
            this.TurnRightButtonA.Location = new System.Drawing.Point(174, 98);
            this.TurnRightButtonA.Name = "TurnRightButtonA";
            this.TurnRightButtonA.Size = new System.Drawing.Size(150, 75);
            this.TurnRightButtonA.TabIndex = 1;
            this.TurnRightButtonA.Text = "Turn Right";
            this.TurnRightButtonA.UseVisualStyleBackColor = true;
            this.TurnRightButtonA.Click += new System.EventHandler(this.TurnRightButton_Click);
            // 
            // SwitchControlButton
            // 
            this.SwitchControlButton.Location = new System.Drawing.Point(497, 128);
            this.SwitchControlButton.Name = "SwitchControlButton";
            this.SwitchControlButton.Size = new System.Drawing.Size(134, 39);
            this.SwitchControlButton.TabIndex = 9;
            this.SwitchControlButton.Text = "Switch Controls";
            this.SwitchControlButton.UseVisualStyleBackColor = true;
            this.SwitchControlButton.Click += new System.EventHandler(this.SwitchControlButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1268, 635);
            this.Controls.Add(this.SwitchControlButton);
            this.Controls.Add(this.AutonomousControlGroup);
            this.Controls.Add(this.ManualControlGroup);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ManualControlGroup.ResumeLayout(false);
            this.AutonomousControlGroup.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button ForwardButton;
        private System.Windows.Forms.Button TurnRightButtonM;
        private System.Windows.Forms.Button BackButton;
        private System.Windows.Forms.Button TurnLeftButtonM;
        private System.Windows.Forms.Button StopButton;
        private System.Windows.Forms.GroupBox ManualControlGroup;
        private System.Windows.Forms.GroupBox AutonomousControlGroup;
        private System.Windows.Forms.Button RoomRightButton;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button RoomLeftButton;
        private System.Windows.Forms.Button TurnLeftButtonA;
        private System.Windows.Forms.Button TurnRightButtonA;
        private System.Windows.Forms.Button SwitchControlButton;
    }
}

