object frmOBJE: TfrmOBJE
  Left = 154
  Top = 182
  Width = 413
  Height = 395
  Caption = 'obje'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 200
    Width = 217
    Height = 153
    Caption = 'Damage Multipliers'
    TabOrder = 1
    object Label10: TLabel
      Left = 136
      Top = 52
      Width = 9
      Height = 13
      Caption = 'to'
    end
    object Label9: TLabel
      Left = 29
      Top = 28
      Width = 44
      Height = 13
      Caption = 'Kinetic:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label7: TLabel
      Left = 136
      Top = 28
      Width = 9
      Height = 13
      Caption = 'to'
    end
    object Label17: TLabel
      Left = 40
      Top = 124
      Width = 33
      Height = 13
      Caption = 'Sync:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label16: TLabel
      Left = 136
      Top = 124
      Width = 9
      Height = 13
      Caption = 'to'
    end
    object Label15: TLabel
      Left = 15
      Top = 100
      Width = 58
      Height = 13
      Caption = 'Electrical:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label14: TLabel
      Left = 136
      Top = 100
      Width = 9
      Height = 13
      Caption = 'to'
    end
    object Label13: TLabel
      Left = 25
      Top = 76
      Width = 48
      Height = 13
      Caption = 'Burning:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 136
      Top = 76
      Width = 9
      Height = 13
      Caption = 'to'
    end
    object Label11: TLabel
      Left = 14
      Top = 52
      Width = 59
      Height = 13
      Caption = 'Explosive:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object edtDmgSyncHi: TEdit
      Left = 152
      Top = 120
      Width = 49
      Height = 21
      TabOrder = 9
      Text = '1.0'
    end
    object edtDmgElectricalLo: TEdit
      Left = 80
      Top = 96
      Width = 49
      Height = 21
      TabOrder = 6
      Text = '1.0'
    end
    object edtDmgElectricalHi: TEdit
      Left = 152
      Top = 96
      Width = 49
      Height = 21
      TabOrder = 7
      Text = '1.0'
    end
    object edtDmgBurningHi: TEdit
      Left = 152
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 5
      Text = '1.0'
    end
    object edtDmgBurningLo: TEdit
      Left = 80
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '1.0'
    end
    object edtDmgExplosiveHi: TEdit
      Left = 152
      Top = 48
      Width = 49
      Height = 21
      TabOrder = 3
      Text = '1.0'
    end
    object edtDmgExplosiveLo: TEdit
      Left = 80
      Top = 48
      Width = 49
      Height = 21
      TabOrder = 2
      Text = '1.0'
    end
    object edtDmgKineticHi: TEdit
      Left = 152
      Top = 24
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '1.0'
    end
    object edtDmgSyncLo: TEdit
      Left = 80
      Top = 120
      Width = 49
      Height = 21
      TabOrder = 8
      Text = '1.0'
    end
    object edtDmgKineticLo: TEdit
      Left = 80
      Top = 24
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '1.0'
    end
  end
  object GroupBox2: TGroupBox
    Left = 240
    Top = 200
    Width = 153
    Height = 153
    Caption = 'Flags'
    TabOrder = 2
    object chkDrawSelection: TCheckBox
      Left = 16
      Top = 40
      Width = 121
      Height = 17
      Caption = 'Draw Selection Box'
      TabOrder = 1
    end
    object chkDrawStatus: TCheckBox
      Left = 16
      Top = 56
      Width = 105
      Height = 17
      Caption = 'Draw Status Bars'
      TabOrder = 2
    end
    object chkIgnoreCollision: TCheckBox
      Left = 16
      Top = 24
      Width = 97
      Height = 17
      Caption = 'Ignore Collisions'
      TabOrder = 0
    end
    object chkUnused1: TCheckBox
      Left = 16
      Top = 72
      Width = 105
      Height = 17
      Caption = 'Unused 1'
      TabOrder = 3
    end
    object chkUnused2: TCheckBox
      Left = 16
      Top = 88
      Width = 105
      Height = 17
      Caption = 'Unused 2'
      TabOrder = 4
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 8
    Width = 217
    Height = 177
    Caption = 'Properties'
    TabOrder = 0
    object Label1: TLabel
      Left = 39
      Top = 28
      Width = 37
      Height = 13
      Caption = 'Armor:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 136
      Top = 28
      Width = 9
      Height = 13
      Caption = 'to'
    end
    object Label3: TLabel
      Left = 30
      Top = 52
      Width = 46
      Height = 13
      Caption = 'Shields:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 136
      Top = 52
      Width = 9
      Height = 13
      Caption = 'to'
    end
    object Label5: TLabel
      Left = 42
      Top = 76
      Width = 34
      Height = 13
      Caption = 'Mass:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label8: TLabel
      Left = 32
      Top = 100
      Width = 44
      Height = 13
      Caption = 'Radius:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 34
      Top = 124
      Width = 42
      Height = 13
      Caption = 'Height:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object edtArmorLo: TEdit
      Left = 80
      Top = 24
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '100.0'
    end
    object edtArmorHi: TEdit
      Left = 152
      Top = 24
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '100.0'
    end
    object edtShieldLo: TEdit
      Left = 80
      Top = 48
      Width = 49
      Height = 21
      TabOrder = 2
      Text = '100.0'
    end
    object edtShieldHi: TEdit
      Left = 152
      Top = 48
      Width = 49
      Height = 21
      TabOrder = 3
      Text = '100.0'
    end
    object edtMass: TEdit
      Left = 80
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '100.0'
    end
    object edtRadius: TEdit
      Left = 80
      Top = 96
      Width = 49
      Height = 21
      TabOrder = 5
      Text = '5.0'
    end
    object edtHeight: TEdit
      Left = 80
      Top = 120
      Width = 49
      Height = 21
      TabOrder = 6
      Text = '5.0'
    end
  end
  object btnCancel: TButton
    Left = 320
    Top = 40
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = btnCancelClick
  end
  object btnSave: TButton
    Left = 320
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Save'
    Default = True
    TabOrder = 3
    OnClick = btnSaveClick
  end
end
