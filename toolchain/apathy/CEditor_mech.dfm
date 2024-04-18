object frmMECH: TfrmMECH
  Left = 318
  Top = 228
  Width = 808
  Height = 710
  Caption = 'mech'
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
  object Label15: TLabel
    Left = 348
    Top = 356
    Width = 82
    Height = 13
    Alignment = taRightJustify
    Caption = 'Radar Radius:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Layout = tlCenter
  end
  object Label16: TLabel
    Left = 348
    Top = 380
    Width = 82
    Height = 13
    Alignment = taRightJustify
    Caption = 'Vision Radius:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Layout = tlCenter
  end
  object btnSave: TButton
    Left = 568
    Top = 496
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 0
    OnClick = btnSaveClick
  end
  object btnCancel: TButton
    Left = 560
    Top = 552
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 1
    OnClick = btnCancelClick
  end
  object SpeedMult: TGroupBox
    Left = 384
    Top = 8
    Width = 201
    Height = 265
    Caption = 'Speed Multipiers'
    TabOrder = 2
    object Label1: TLabel
      Left = 92
      Top = 64
      Width = 37
      Height = 13
      Alignment = taRightJustify
      BiDiMode = bdLeftToRight
      Caption = 'Grass:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      Layout = tlBottom
    end
    object Label2: TLabel
      Left = 68
      Top = 88
      Width = 61
      Height = 13
      Alignment = taRightJustify
      BiDiMode = bdLeftToRight
      Caption = 'Pavement:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      Layout = tlBottom
    end
    object Label3: TLabel
      Left = 34
      Top = 112
      Width = 95
      Height = 13
      Alignment = taRightJustify
      Caption = 'Water (Shallow):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlBottom
    end
    object Label4: TLabel
      Left = 48
      Top = 136
      Width = 81
      Height = 13
      Alignment = taRightJustify
      Caption = 'Water (Deep):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlBottom
    end
    object Label5: TLabel
      Left = 92
      Top = 160
      Width = 37
      Height = 13
      Alignment = taRightJustify
      Caption = 'Brush:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlBottom
    end
    object Label6: TLabel
      Left = 88
      Top = 184
      Width = 41
      Height = 13
      Alignment = taRightJustify
      Caption = 'Rocky:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlBottom
    end
    object Label7: TLabel
      Left = 16
      Top = 208
      Width = 113
      Height = 13
      Alignment = taRightJustify
      Caption = 'Ground Impassable:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlCenter
    end
    object Label8: TLabel
      Left = 42
      Top = 232
      Width = 87
      Height = 13
      Alignment = taRightJustify
      Caption = 'Air Impassable:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlBottom
    end
    object Label14: TLabel
      Left = 56
      Top = 24
      Width = 73
      Height = 13
      Alignment = taRightJustify
      BiDiMode = bdLeftToRight
      Caption = 'Base Speed:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      Layout = tlBottom
    end
    object edtGround: TEdit
      Left = 136
      Top = 64
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '1'
    end
    object edtPave: TEdit
      Left = 136
      Top = 88
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '1'
    end
    object edtShallow: TEdit
      Left = 136
      Top = 112
      Width = 49
      Height = 21
      TabOrder = 2
      Text = '1'
    end
    object edtDeep: TEdit
      Left = 136
      Top = 136
      Width = 49
      Height = 21
      TabOrder = 3
      Text = '1'
    end
    object edtBrush: TEdit
      Left = 136
      Top = 160
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '1'
    end
    object edtRocky: TEdit
      Left = 136
      Top = 184
      Width = 49
      Height = 21
      TabOrder = 5
      Text = '1'
    end
    object edtGrndImpas: TEdit
      Left = 136
      Top = 208
      Width = 49
      Height = 21
      TabOrder = 6
      Text = '1'
    end
    object edtAirImpas: TEdit
      Left = 136
      Top = 232
      Width = 49
      Height = 21
      TabOrder = 7
      Text = '1'
    end
    object edtBaseSpeed: TEdit
      Left = 136
      Top = 24
      Width = 49
      Height = 21
      TabOrder = 8
      Text = '1'
    end
  end
  object Props: TGroupBox
    Left = 8
    Top = 8
    Width = 193
    Height = 81
    Caption = 'Properties'
    TabOrder = 3
    object Label9: TLabel
      Left = 14
      Top = 24
      Width = 51
      Height = 13
      Alignment = taRightJustify
      Caption = 'obje tag:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlCenter
    end
    object Label10: TLabel
      Left = 12
      Top = 48
      Width = 53
      Height = 13
      Alignment = taRightJustify
      Caption = 'imgc tag:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlBottom
    end
    object edtObje: TEdit
      Left = 72
      Top = 24
      Width = 113
      Height = 21
      TabOrder = 0
      Text = 'edtObje'
    end
    object edtImgc: TEdit
      Left = 72
      Top = 48
      Width = 113
      Height = 21
      TabOrder = 1
      Text = 'edtImgc'
    end
  end
  object SequenceIndx: TGroupBox
    Left = 8
    Top = 96
    Width = 193
    Height = 73
    Caption = 'Sequence Indices'
    TabOrder = 4
    object Label11: TLabel
      Left = 16
      Top = 24
      Width = 25
      Height = 13
      Alignment = taRightJustify
      Caption = 'idle:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlBottom
    end
    object Label12: TLabel
      Left = 10
      Top = 48
      Width = 31
      Height = 13
      Alignment = taRightJustify
      Caption = 'walk:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlCenter
    end
    object Label13: TLabel
      Left = 111
      Top = 12
      Width = 23
      Height = 13
      Alignment = taRightJustify
      Caption = 'fire:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlCenter
    end
    object edtIdle: TEdit
      Left = 48
      Top = 20
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '1'
    end
    object edtWalk: TEdit
      Left = 48
      Top = 44
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '1'
    end
    object edtFire: TEdit
      Left = 136
      Top = 28
      Width = 49
      Height = 21
      TabOrder = 2
      Text = '1'
    end
  end
  object GroupBox1: TGroupBox
    Left = 208
    Top = 8
    Width = 169
    Height = 265
    Caption = 'Attacks: '
    TabOrder = 5
    object Label22: TLabel
      Left = 14
      Top = 16
      Width = 43
      Height = 13
      Alignment = taRightJustify
      Caption = 'Mental:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlBottom
    end
    object lstMentAttacks: TListBox
      Left = 8
      Top = 32
      Width = 153
      Height = 65
      ItemHeight = 13
      TabOrder = 0
      OnClick = lstMentAttacksClick
    end
    object btnAddMent: TBitBtn
      Left = 104
      Top = 128
      Width = 25
      Height = 25
      TabOrder = 1
      OnClick = btnAddMentClick
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000C40E0000C40E00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF008000008000FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        8000008000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF008000008000FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        8000008000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF008000008000FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00800000800000800000800000800000
        8000008000008000008000008000008000008000FFFFFFFFFFFFFFFFFFFFFFFF
        0080000080000080000080000080000080000080000080000080000080000080
        00008000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        8000008000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF008000008000FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        8000008000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF008000008000FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        8000008000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
    end
    object btnDeleteMent: TBitBtn
      Left = 136
      Top = 128
      Width = 25
      Height = 25
      TabOrder = 2
      OnClick = btnDeleteMentClick
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000C40E0000C40E00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        000080000080FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000
        80000080FFFFFFFFFFFFFFFFFFFFFFFF000080000080000080FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFF000080000080000080FFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFF000080000080000080FFFFFFFFFFFFFFFFFFFFFFFF0000800000800000
        80FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000080000080000080FF
        FFFFFFFFFF000080000080000080FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFF000080000080000080000080000080000080FFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00008000
        0080000080000080FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF000080000080000080000080FFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00008000008000
        0080000080000080000080FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFF000080000080000080FFFFFFFFFFFF000080000080000080FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000080000080000080FFFFFFFF
        FFFFFFFFFFFFFFFF000080000080000080FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        000080000080000080FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000800000
        80000080FFFFFFFFFFFFFFFFFFFFFFFF000080000080FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFF000080000080FFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
    end
    object cmbMentName: TComboBox
      Left = 8
      Top = 104
      Width = 153
      Height = 21
      ItemHeight = 13
      TabOrder = 3
      Text = 'cmbMentName'
      OnChange = cmbMentNameChange
    end
  end
  object edtVisionRange: TEdit
    Left = 432
    Top = 376
    Width = 121
    Height = 21
    TabOrder = 6
    Text = 'edtVisionRange'
  end
  object edtRadarRange: TEdit
    Left = 432
    Top = 352
    Width = 121
    Height = 21
    TabOrder = 7
    Text = 'edtRadarRange'
  end
end
