
package require Ttk


### Vars ############

set fname "Untitled" 

### GUI ############

set xf [ttk::frame .f]
set st [ttk::frame .status -relief sunken ]

### MENU BAR ############################
set mb [menu .mbar]

menu $mb.file -tearoff 0
$mb.file add command -label "New"
$mb.file add command -label "Open ..." -command open_cb
$mb.file add command -label "Save"
$mb.file add command -label "Save as ..."
$mb.file add separator
$mb.file add command -label "Quit"

$mb add cascade -label "File" -menu $mb.file

menu $mb.ptn -tearoff 0
$mb.ptn add command -label "Clear"    -command {clear_cb .pw.top.pat}
$mb.ptn add command -label "Load ..." -command {load_cb .pw.top.pat "-P"}
$mb.ptn add command -label "Export .pmx"
$mb.ptn add separator
$mb.ptn add command -label "Explain current"
$mb.ptn add command -label "Explain all"
$mb.ptn add separator
$mb.ptn add command -label "Pmx Syntax"

$mb add cascade -label "Patterns" -menu $mb.ptn

menu $mb.txt -tearoff 0
$mb.txt add command -label "Clear"     -command {clear_cb .pw.btm.txt}
$mb.txt add command -label "Load ..."  -command {load_cb .pw.btm.txt "-P"}
$mb.txt add separator
$mb.txt add command -label "Test current"
$mb.txt add command -label "Test all"
$mb.txt add command -label "Trace parsing"


$mb add cascade -label "Text" -menu $mb.txt

menu $mb.help -tearoff 0
$mb.help add command -label "Help"
$mb.help add command -label "Pmx Syntax"
$mb.help add separator
$mb.help add command -label "About"

$mb add cascade -label "Help" -menu $mb.help

. configure -menu .mbar


### MAIN WINDOW ##############

ttk::panedwindow .pw -orient vertical

ttk::labelframe .pw.top -text "Patterns"
ttk::labelframe .pw.btm -text "Text"

text .pw.top.pat -undo 1 -height 10\
     -yscrollcommand [list .pw.top.sy set] \
     -xscrollcommand [list .pw.top.sx set]   
ttk::scrollbar .pw.top.sy -command [list .pw.top.pat yview] -orient v
ttk::scrollbar .pw.top.sx -command [list .pw.top.pat xview] -orient h

grid .pw.top.pat  -row 0 -column 0 -sticky news 
grid .pw.top.sy   -row 0 -column 1 -sticky ns
grid .pw.top.sx   -row 1 -column 0 -sticky we

grid rowconfigure .pw.top 0 -weight 100
grid columnconfigure .pw.top 0 -weight 100

text .pw.btm.txt -undo 1 -height 10 \
     -yscrollcommand [list .pw.btm.sy set] \
     -xscrollcommand [list .pw.btm.sx set]   
ttk::scrollbar .pw.btm.sy -command [list .pw.btm.txt yview] -orient v
ttk::scrollbar .pw.btm.sx -command [list .pw.btm.txt xview] -orient h

grid .pw.btm.txt  -row 0 -column 0 -sticky news 
grid .pw.btm.sy   -row 0 -column 1 -sticky ns
grid .pw.btm.sx   -row 1 -column 0 -sticky we

grid rowconfigure .pw.btm 0    -pad 2 -weight 100
grid columnconfigure .pw.btm 0 -pad 2 -weight 100

.pw add .pw.top -weight 50
.pw add .pw.btm -weight 50

pack .pw -expand 1 -fill both

#bind .pw.top.pat <KeyPress-Return> {
#  tk_messageBox -message "Return!" -type ok
#  break
#}
 
## Popup menus
bind .pw.btm.txt <3> {tk_popup $mb.txt %X %Y}
bind .pw.top.pat <3> {tk_popup $mb.ptn %X %Y}

## Toplevel

wm title . "PMX shell - $fname"
wm iconbitmap . -default "pmxshell.ico"

### Commands 

proc open_cb {} {

  set fn [tk_getOpenFile]
  
  if {$fn != "" } {
    tk_messageBox -message "Selected \"$fn\"" -type ok
  }
}

proc load_cb {wdg flg} {

  set fn [tk_getOpenFile]
  
  if {$fn != "" } {
    set status 0
    if {[catch {exec pmxmm $flg $fn} results options]} {
      set details [dict get $options -errorcode]
      if {[lindex $details 0] eq "CHILDSTATUS"} {
        tk_messageBox -icon error -title "PMXshell error" -message "$results" -type ok
        set status [lindex $details 2]
      } else {
        tk_messageBox -message "$options" -type ok
        # Some kind of unexpected failure
      }
    } else {
      $wdg replace 1.0 end "$results"
    }
  }
}

proc clear_cb wdg {
  $wdg delete 1.0 end
}


