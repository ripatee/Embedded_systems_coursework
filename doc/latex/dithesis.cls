%% 
%% This is file `dithesis.cls', modified from standart 
%% Latex file 'report.cls'
%%           Harri Saarnisaari 2022 (original 1996)
%% 
%% \CharacterTable
%%  {Upper-case    \A\B\C\D\E\F\G\H\I\J\K\L\M\N\O\P\Q\R\S\T\U\V\W\X\Y\Z
%%   Lower-case    \a\b\c\d\e\f\g\h\i\j\k\l\m\n\o\p\q\r\s\t\u\v\w\x\y\z
%%   Digits        \0\1\2\3\4\5\6\7\8\9
%%   Exclamation   \!     Double quote  \"     Hash (number) \#
%%   Dollar        \$     Percent       \%     Ampersand     \&
%%   Acute accent  \'     Left paren    \(     Right paren   \)
%%   Asterisk      \*     Plus          \+     Comma         \,
%%   Minus         \-     Point         \.     Solidus       \/
%%   Colon         \:     Semicolon     \;     Less than     \<
%%   Equals        \=     Greater than  \>     Question mark \?
%%   Commercial at \@     Left bracket  \[     Backslash     \\
%%   Right bracket \]     Circumflex    \^     Underscore    \_
%%   Grave accent  \`     Left brace    \{     Vertical bar  \|
%%   Right brace   \}     Tilde         \~}
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{dithesis}
              [2022/4/28
 DI-thesis class for Univ. Oulu ITEE]
\usepackage{newtxtext} %times new roman
\usepackage{newtxmath}%times new roman
\usepackage{graphicx}

\newif\ifsymbolspage\symbolspagetrue
\newif\if@restonecol
\newif\if@titlepage
\newif\if@suomi
\@suomifalse
\@titlepagetrue
\newif\if@openright
\newif\if@openbib
\@openbibfalse
\newif\ifappendix \appendixfalse    % appendix flag
\DeclareOption{a4paper}
   {\setlength\paperheight {297mm}%
    \setlength\paperwidth  {210mm}}
\DeclareOption{a5paper}
   {\setlength\paperheight {210mm}%
    \setlength\paperwidth  {148mm}}
\DeclareOption{b5paper}
   {\setlength\paperheight {250mm}%
    \setlength\paperwidth  {176mm}}
\DeclareOption{letterpaper}
   {\setlength\paperheight {11in}%
    \setlength\paperwidth  {8.5in}}
\DeclareOption{legalpaper}
   {\setlength\paperheight {14in}%
    \setlength\paperwidth  {8.5in}}
\DeclareOption{executivepaper}
   {\setlength\paperheight {10.5in}%
    \setlength\paperwidth  {7.25in}}
\DeclareOption{landscape}
   {\setlength\@tempdima   {\paperheight}%
    \setlength\paperheight {\paperwidth}%
    \setlength\paperwidth  {\@tempdima}}
\DeclareOption{10pt}{\typeout{I'am usign 12pt anyway}}
\DeclareOption{11pt}{\typeout{I'am using 12pt anyway}}
\DeclareOption{12pt}{}
\DeclareOption{oneside}{\@twosidefalse \@mparswitchfalse}
\DeclareOption{twoside}{\@twosidetrue  \@mparswitchtrue}
\DeclareOption{draft}{\setlength\overfullrule{5pt}}
\DeclareOption{final}{\setlength\overfullrule{0pt}}
\DeclareOption{titlepage}{\@titlepagetrue}
\DeclareOption{notitlepage}{\@titlepagefalse}
\DeclareOption{openright}{\@openrighttrue}
\DeclareOption{openany}{\@openrightfalse}
\DeclareOption{onecolumn}{\@twocolumnfalse}
\DeclareOption{twocolumn}{\@twocolumntrue}
\DeclareOption{leqno}{\input{leqno.clo}}
\DeclareOption{fleqn}{\input{fleqn.clo}}
\DeclareOption{openbib}{\@openbibtrue}
\DeclareOption{suomi}{\@suomitrue}
\DeclareOption{nosymbolspage}{\symbolspagefalse}
\ExecuteOptions{a4paper,12pt,oneside,onecolumn,final,openany} 
\ProcessOptions
\if@compatibility
 \typeout{USE DOCUMENTCLASS instead of documentstyle to get desired result!}
\fi

%%
%%latex file size12.clo is included and modified
%% 
\renewcommand{\normalsize}{%
   \@setfontsize\normalsize\@xiipt{14}%
   \abovedisplayskip 14\p@ \@plus3\p@ \@minus7\p@
   \abovedisplayshortskip 14\p@ \@plus3\p@ \@minus2\p@ 
   \belowdisplayshortskip 14\p@ \@plus3\p@ \@minus2\p@ 
   \belowdisplayskip \abovedisplayskip
   \let\@listi\@listI}
\normalsize
\newcommand{\small}{%
   \@setfontsize\small\@xipt{13}%
   \abovedisplayskip 13\p@ \@plus3\p@ \@minus6\p@
   \abovedisplayshortskip 13\p@ \@plus3\p@ \@minus2\p@
   \belowdisplayshortskip 13\p@ \@plus3\p@ \@minus2\p@
   \def\@listi{\leftmargin\leftmargini
               \topsep 9\p@ \@plus3\p@ \@minus5\p@
               \parsep 4.5\p@ \@plus2\p@ \@minus\p@
               \itemsep \parsep}%
   \belowdisplayskip \abovedisplayskip
}
\newcommand{\footnotesize}{%
   \@setfontsize\footnotesize\@xpt\@xiipt
   \abovedisplayskip 10\p@ \@plus2\p@ \@minus5\p@
   \abovedisplayshortskip \z@ \@plus3\p@
   \belowdisplayshortskip 6\p@ \@plus3\p@ \@minus3\p@
   \def\@listi{\leftmargin\leftmargini
               \topsep 6\p@ \@plus2\p@ \@minus2\p@
               \parsep 3\p@ \@plus2\p@ \@minus\p@
               \itemsep \parsep}%
   \belowdisplayskip \abovedisplayskip
}
\newcommand{\scriptsize}{\@setfontsize\scriptsize{10}{12}}
\newcommand{\tiny}{\@setfontsize\tiny{8}{10}}
\newcommand{\large}{\@setfontsize\large{14}{16}}
\newcommand{\Large}{\@setfontsize\Large\@xviipt{22}}
\newcommand{\LARGE}{\@setfontsize\LARGE\@xxpt{25}}
\newcommand{\huge}{\@setfontsize\huge\@xxvpt{30}}
\let\Huge=\huge
\if@twocolumn
  \setlength\parindent{1em}
\else
  \setlength\parindent{0.5cm}              
\fi
\setlength\headheight{12pt}             
\setlength\headsep   {1.1cm}              
\setlength\topskip   {0pt}  
\setlength\hoffset {-0.04cm}
\setlength\footskip{30\p@}
\if@compatibility \setlength\maxdepth{4\p@} \else
\setlength\maxdepth{.5\topskip} \fi
\setlength\@maxdepth\maxdepth
\if@compatibility
  \if@twocolumn
    \setlength\textwidth{410\p@}
  \else
    \setlength\textwidth{390\p@}
  \fi
\else
  \setlength\@tempdima{\paperwidth}
  \addtolength\@tempdima{-2in}
  \setlength\@tempdimb{390\p@}
  \if@twocolumn
    \ifdim\@tempdima>2\@tempdimb\relax
      \setlength\textwidth{2\@tempdimb}
    \else
      \setlength\textwidth{\@tempdima}
    \fi
  \else
    \ifdim\@tempdima>\@tempdimb\relax
      \setlength\textwidth{16cm}           
     \else
      \setlength\textwidth{16cm}           
    \fi
  \fi
\fi
\if@compatibility\else
  \@settopoint\textwidth
\fi
\if@compatibility
  \setlength\textheight{36\baselineskip}
\else
  \setlength\@tempdima{\paperheight}
  \addtolength\@tempdima{-2in}
  \addtolength\@tempdima{-1.5in}
  \divide\@tempdima\baselineskip
  \@tempcnta=\@tempdima
  \setlength\textheight{24.2cm}             
\fi
\addtolength\textheight{\topskip}
\if@compatibility
  \if@twoside
     \setlength\oddsidemargin   {21\p@}
     \setlength\evensidemargin  {59\p@}
     \setlength\marginparwidth {85\p@}
  \else
     \setlength\oddsidemargin   {39.5\p@}
     \setlength\evensidemargin  {39.5\p@}
     \setlength\marginparwidth  {68\p@}
  \fi
  \if@twocolumn
     \setlength\oddsidemargin  {30\p@}
     \setlength\evensidemargin {30\p@}
     \setlength\marginparwidth {48\p@}
  \fi
\else
  \if@twoside
    \setlength\@tempdima        {\paperwidth}
    \addtolength\@tempdima      {-\textwidth}
    \setlength\oddsidemargin    {.4\@tempdima}
    \addtolength\oddsidemargin  {-1in}
    \setlength\marginparwidth   {.6\@tempdima}
    \addtolength\marginparwidth {-0.4in}
  \else
    \setlength\@tempdima        {\paperwidth}
    \addtolength\@tempdima      {-\textwidth}
    \setlength\oddsidemargin    {0cm}%{1.96cm}           
    \addtolength\oddsidemargin  {0pt}               
    \setlength\marginparwidth   {0cm}%{.5\@tempdima}
    \addtolength\marginparwidth {0cm}%{-.4in}
  \fi
  \ifdim \marginparwidth >2in
     \setlength\marginparwidth{2in}
  \fi
  \@settopoint\oddsidemargin
  \@settopoint\marginparwidth
  \setlength\evensidemargin  {\paperwidth}
  \addtolength\evensidemargin{-2in}
  \addtolength\evensidemargin{-\textwidth}
  \addtolength\evensidemargin{-\oddsidemargin}
  \@settopoint\evensidemargin
\fi
\if@twocolumn
 \setlength\marginparsep {10\p@}
\else
  \setlength\marginparsep{0cm}%{10\p@}
\fi
\setlength\marginparpush{7\p@}
\if@compatibility
  \setlength\topmargin{27pt}
\else
  \setlength\topmargin{-24pt}   
  \@settopoint\topmargin
\fi
\setlength\footnotesep{8.4\p@}
\setlength{\skip\footins}{10.8\p@ \@plus 4\p@ \@minus 2\p@}
\setlength\floatsep    {28\p@}
\setlength\textfloatsep{28\p@}
\setlength\intextsep   {28\p@}
\setlength\dblfloatsep    {14\p@ \@plus 2\p@ \@minus 4\p@}
\setlength\dbltextfloatsep{20\p@ \@plus 2\p@ \@minus 4\p@}
\setlength\@fptop{0\p@ \@plus 1fil}
\setlength\@fpsep{10\p@ \@plus 2fil}
\setlength\@fpbot{0\p@ \@plus 1fil}
\setlength\@dblfptop{0\p@ \@plus 1fil}
\setlength\@dblfpsep{10\p@ \@plus 2fil}
\setlength\@dblfpbot{0\p@ \@plus 1fil}
\setlength\partopsep{3\p@ \@plus 2\p@ \@minus 2\p@}
\def\@listI{\leftmargin\leftmargini
            \parsep 5\p@  \@plus2.5\p@ \@minus\p@
            \topsep 10\p@ \@plus4\p@   \@minus6\p@
            \itemsep5\p@  \@plus2.5\p@ \@minus\p@}
\let\@listi\@listI
\@listi
\def\@listii {\leftmargin\leftmarginii
              \labelwidth\leftmarginii
              \advance\labelwidth-\labelsep
              \topsep    5\p@   \@plus2.5\p@ \@minus\p@
              \parsep    2.5\p@ \@plus\p@    \@minus\p@
              \itemsep   \parsep}
\def\@listiii{\leftmargin\leftmarginiii
              \labelwidth\leftmarginiii
              \advance\labelwidth-\labelsep
              \topsep    2.5\p@\@plus\p@\@minus\p@
              \parsep    \z@
              \partopsep \p@ \@plus\z@ \@minus\p@
              \itemsep   \topsep}
\def\@listiv {\leftmargin\leftmarginiv
              \labelwidth\leftmarginiv
              \advance\labelwidth-\labelsep}
\def\@listv  {\leftmargin\leftmarginv
              \labelwidth\leftmarginv
              \advance\labelwidth-\labelsep}
\def\@listvi {\leftmargin\leftmarginvi
              \labelwidth\leftmarginvi
              \advance\labelwidth-\labelsep}
%% 
%% End of file `size12.clo'.
%%
\setlength\lineskip{1\p@}
\setlength\normallineskip{1\p@}
\renewcommand{\baselinestretch}{}
\setlength\parskip{14\p@}         
\@lowpenalty   51
\@medpenalty  151
\@highpenalty 301
\setcounter{topnumber}{2}
\renewcommand{\topfraction}{.7}
\setcounter{bottomnumber}{1}
\renewcommand{\bottomfraction}{.3}
\setcounter{totalnumber}{3}
\renewcommand{\textfraction}{.2}
\renewcommand{\floatpagefraction}{.5}
\setcounter{dbltopnumber}{2}
\renewcommand{\dbltopfraction}{.7}
\renewcommand{\dblfloatpagefraction}{.5}
\if@twoside
  \def\ps@headings{%
      \let\@oddfoot\@empty\let\@evenfoot\@empty
      \def\@evenhead{\thepage\hfil\slshape\leftmark}%
      \def\@oddhead{{\slshape\rightmark}\hfil\thepage}%
      \let\@mkboth\markboth
    \def\chaptermark##1{%
      \markboth {\uppercase{%
        \ifnum \c@secnumdepth >\m@ne
            \@chapapp\ \thechapter. \ %
        \fi
        ##1}}{}}%
    \def\sectionmark##1{%
      \markright {\uppercase{%
        \ifnum \c@secnumdepth >\z@
          \thesection. \ %
        \fi
        ##1}}}}
\else
  \def\ps@headings{%
    \let\@oddfoot\@empty
       \ifappendix
       \def\@oddhead{{}\hfill{{\appendixname}\ \thechapter/{\thepage}}} 
      \else
    \def\@oddhead{{}\hfil\thepage}% 
    \fi                    
    \let\@mkboth\markboth
    \def\chaptermark##1{%
      \markright {\uppercase{%
        \ifnum \c@secnumdepth >\m@ne
            \@chapapp\ \thechapter. \ %
        \fi
        ##1}}}}
\fi
\def\ps@myheadings{%
    \let\@oddfoot\@empty\let\@evenfoot\@empty
    \def\@evenhead{\thepage\hfil\slshape\leftmark}%
    \def\@oddhead{{}\hfil\appendixname\  \thechapter (\thepage)}%
    \let\@mkboth\@gobbletwo
    \let\chaptermark\@gobble
    \let\sectionmark\@gobble
    }
\if@titlepage
  \newcommand{\maketitle}{\begin{titlepage}%
  \let\footnotesize\small
  \let\footnoterule\relax
  \null%\vfil
  %\vskip 60\p@
  \begin{center}%
  \vspace{-30\p@}
  \if@suomi
      {\includegraphics[width=4cm]{UOULUlogoFI.png}\par
     {\small TIETO- JA SÄHK\"OTEKNIIKAN TIEDEKUNTA \\
     ELEKTRONIIKAN JA TIETOLIIKENNETEKNIIKAN TUTKINTO-OHJELMA}}
      \else
     {\includegraphics[width=4cm]{UOULUlogoEN.png}\par
     {\small FACULTY OF INFORMATION TECHNOLOGY AND ELECTRICAL ENGINEERING \\
     DEGREE PROGRAMME IN ELECTRONICS AND COMMUNICATIONS ENGINEERING}}
     \fi
     
     \vskip 120\p@
     \if@suomi
     {\Large{\bfseries DIPLOMITY\"O} \\ \vspace{20pt} }%
     \else
     {\Large{\bfseries IoT SENSOR} \\ \vspace{20pt} }%
     \fi
    {\Large{\bfseries \@title} \par}%
    \vskip 3em%
    \vspace{60pt}
    {\large
     \lineskip .75em%
      \begin{tabular}[t]{c}%
      \@author \\
      \end{tabular}\par}%
      \vskip 1.5em%
  \end{center}\par
  \@thanks
  \vfil\null
  \end{titlepage}%
  \setcounter{footnote}{0}%
  \let\thanks\relax\let\maketitle\relax
  \gdef\@thanks{}\gdef\@author{}\gdef\@title{}}
\else
\newcommand{\maketitle}{\par
  \begingroup
    \renewcommand{\thefootnote}{\fnsymbol{footnote}}%
    \def\@makefnmark{\hbox to\z@{$\m@th^{\@thefnmark}$\hss}}%
    \long\def\@makefntext##1{\parindent 1em\noindent
            \hbox to1.8em{\hss$\m@th^{\@thefnmark}$}##1}%
    \if@twocolumn
      \ifnum \col@number=\@ne
        \@maketitle
      \else
        \twocolumn[\@maketitle]%
      \fi
    \else
      \newpage
      \global\@topnum\z@   % Prevents figures from going at top of page.
      \@maketitle
    \fi
    \thispagestyle{plain}\@thanks
  \endgroup
  \setcounter{footnote}{0}%
  \let\thanks\relax
  \let\maketitle\relax\let\@maketitle\relax
  \gdef\@thanks{}\gdef\@author{}\gdef\@title{}}
\def\@maketitle{%
  \newpage
  \null
  \vskip 2em%
  \begin{center}%
    {\LARGE \@title \par}%
    \vskip 1.5em%
    {\large
      \lineskip .5em%
      \begin{tabular}[t]{c}%
        \@author
      \end{tabular}\par}%
    \vskip 1em%
    {\large \@date}%
  \end{center}%
  \par
  \vskip 1.5em}
\fi
\newcommand*{\chaptermark}[1]{}
\setcounter{secnumdepth}{3}             
\newcounter {part}
\newcounter {chapter}
\newcounter {section}[chapter]
\newcounter {subsection}[section]
\newcounter {subsubsection}[subsection]
\newcounter {paragraph}[subsubsection]
\newcounter {subparagraph}[paragraph]
\renewcommand{\thepart}         {\Roman{part}}
\renewcommand{\thechapter}      {\arabic{chapter}}
\renewcommand{\thesection}      {\thechapter.\arabic{section}}
\renewcommand{\thesubsection}   {\thesection.\arabic{subsection}}
\renewcommand{\thesubsubsection}{\thesubsection.\arabic{subsubsection}}
\renewcommand{\theparagraph}    {\thesubsubsection.\arabic{paragraph}}
\renewcommand{\thesubparagraph} {\theparagraph.\arabic{subparagraph}}

%%% Periods for sectioning commands
%%% (modified from latex kernel)
%%%
\def\@sect#1#2#3#4#5#6[#7]#8{\ifnum #2>\c@secnumdepth
     \def\@svsec{}\else 
     \refstepcounter{#1}\edef\@svsec{\csname the#1\endcsname\ }\fi
     \@tempskipa #5\relax
      \ifdim \@tempskipa>\z@ 
        \begingroup #6\relax
          \@hangfrom{\hskip #3\relax\@svsec}{\interlinepenalty \@M #8\par}
        \endgroup
       \csname #1mark\endcsname{#7}\addcontentsline
         {toc}{#1}{\ifnum #2>\c@secnumdepth \else
                      \protect\numberline{\csname the#1\endcsname}\fi
                    #7}\else
        \def\@svsechd{#6\hskip #3\@svsec #8\csname #1mark\endcsname
                      {#7}\addcontentsline
                           {toc}{#1}{\ifnum #2>\c@secnumdepth \else
                             \protect\numberline{\csname the#1\endcsname.}\fi
                       #7}}\fi
     \@xsect{#5}}
%%%% end


\newcommand{\@chapapp}{\chaptername}
\newcommand{\part}{\cleardoublepage
                 \thispagestyle{plain}%
                 \if@twocolumn
                     \onecolumn
                     \@tempswatrue
                   \else
                     \@tempswafalse
                 \fi
                 \hbox{}\vfil
                 \secdef\@part\@spart}

\def\@part[#1]#2{%
    \ifnum \c@secnumdepth >-2\relax
      \refstepcounter{part}%
      \addcontentsline{toc}{part}{\thepart\hspace{1em}#1}%
    \else
      \addcontentsline{toc}{part}{#1}%
    \fi
    \markboth{}{}
    {\centering
     \interlinepenalty \@M
     \reset@font
     \ifnum \c@secnumdepth >-2\relax
       \huge\bfseries \partname~\thepart
       \par
       \vskip 20\p@
     \fi
     \Huge \bfseries #2\par}%
    \@endpart}
\def\@spart#1{%
    {\centering
     \interlinepenalty \@M
     \reset@font
     \Huge \bfseries #1\par}%
    \@endpart}
\def\@endpart{\vfil\newpage
              \if@twoside
                \hbox{}%
                \thispagestyle{empty}%
                \newpage
              \fi
              \if@tempswa
                \twocolumn
              \fi}
\newcommand{\chapter}{\if@openright\cleardoublepage\else\clearpage\fi
   \if@pagestyleempty \pagestyle{headings} \fi
%\ifappendix \pagestyle{myheadings}\setcounter{page}{1}\fi
                    \global\@topnum\z@
                    \@afterindentfalse
                    \secdef\@chapter\@schapter}
\def\@chapter[#1]#2{\ifnum \c@secnumdepth > \m@ne 
                         \refstepcounter{chapter}%
                         \typeout{\@chapapp\space\thechapter.}%
                         % \ifappendix   %appendix case
                         %\else  
                         \addcontentsline{toc}{chapter}{\protect\numberline{\thechapter}#1}%
                    % \fi
                    \else
                      \addcontentsline{toc}{chapter}{#1}%
                    \fi
                    \chaptermark{#1}%
                    \addtocontents{lof}{\protect\addvspace{10\p@}}%
                    \addtocontents{lot}{\protect\addvspace{10\p@}}%
                    \if@twocolumn
                      \@topnewpage[\@makechapterhead{#2}]%
                    \else
                      \@makechapterhead{#2}%
                      \@afterheading
                    \fi}


\def\@makechapterhead#1{%
\ifappendix \else  \vspace*{-34\p@}%
 {\parindent \z@ \raggedright \reset@font
    \ifnum \c@secnumdepth >\m@ne
         \begin{center}\large\bfseries \thechapter \hspace{0.7em}
    \fi
    \interlinepenalty\@M
    \large\bfseries #1\end{center}\par\nobreak
    \vskip 12\p@                                    
  }\fi}
\def\@schapter#1{\if@twocolumn
                   \@topnewpage[\@makeschapterhead{#1}]%
                 \else
                   \@makeschapterhead{#1}%
                   \@afterheading
                 \fi}
\def\@makeschapterhead#1{%
\ifappendix \else   \vspace*{-18\p@}%
{\parindent \z@ \raggedright
    \reset@font
    \interlinepenalty\@M 
    \begin{center}\large \bfseries  #1\end{center}\par\nobreak
    \vskip 12\p@
  }\fi}
\newcommand{\section}{\@startsection {section}{1}{0pt}%{\z@}%
                                  {-28pt \@plus -4pt \@minus 2pt}% 
                                  {14pt \@plus4pt}%                    
                                   {\reset@font\normalsize\bfseries\center}} %     
\newcommand{\subsection}{\@startsection{subsection}{2}{0pt}%{\z@}%
                                   {-28pt \@plus -4pt \@minus -2pt}%   
                                    {14pt \@plus 4pt}%                    
                                     {\reset@font\normalsize\itshape\center}}% 
\newcommand{\subsubsection}{\@startsection{subsubsection}{3}{0pt}%{\z@}%
                                     {-28pt \@plus -4pt \@minus -2pt}%   
                                     {14pt \@plus 4pt}%                    
                                     {\reset@font\normalsize\itshape\center}} %  
\newcommand{\paragraph}{\@startsection{paragraph}{4}{0pt}%{\z@}%
                                    {-14pt \@plus2pt \@minus2pt}%       
                                    {14pt} %{-1em}%                                 
                                    {\reset@font\normalsize\bfseries}}          
\newcommand{\subparagraph}{\@startsection{subparagraph}{5}{\parindent}%
                                       {3.25ex \@plus1ex \@minus .2ex}%
                                       {-1em}%
                                      {\reset@font\normalsize\bfseries}}
\if@twocolumn
  \setlength\leftmargini  {2em}
\else
  \setlength\leftmargini  {2.5em}
\fi
\setlength\leftmarginii  {2.2em}
\setlength\leftmarginiii {1.87em}
\setlength\leftmarginiv  {1.7em}
\if@twocolumn
  \setlength\leftmarginv  {.5em}
  \setlength\leftmarginvi {.5em}
\else
  \setlength\leftmarginv  {1em}
  \setlength\leftmarginvi {1em}
\fi
\setlength\leftmargin    {\leftmargini}
\setlength  \labelsep  {.5em}
\setlength  \labelwidth{\leftmargini}
\addtolength\labelwidth{-\labelsep}
\@beginparpenalty -\@lowpenalty
\@endparpenalty   -\@lowpenalty
\@itempenalty     -\@lowpenalty
\renewcommand{\theenumi}{\arabic{enumi}}
\renewcommand{\theenumii}{\alph{enumii}}
\renewcommand{\theenumiii}{\roman{enumiii}}
\renewcommand{\theenumiv}{\Alph{enumiv}}
\newcommand{\labelenumi}{\theenumi.}
\newcommand{\labelenumii}{(\theenumii)}
\newcommand{\labelenumiii}{\theenumiii.}
\newcommand{\labelenumiv}{\theenumiv.}
\renewcommand{\p@enumii}{\theenumi}
\renewcommand{\p@enumiii}{\theenumi(\theenumii)}
\renewcommand{\p@enumiv}{\p@enumiii\theenumiii}
\newcommand{\labelitemi}{$\m@th\bullet$}
\newcommand{\labelitemii}{\normalfont\bfseries --}
\newcommand{\labelitemiii}{$\m@th\ast$}
\newcommand{\labelitemiv}{$\m@th\cdot$}
\newenvironment{description}
               {\list{}{\labelwidth\z@ \itemindent-\leftmargin
                        \let\makelabel\descriptionlabel}}
               {\endlist}
\newcommand{\descriptionlabel}[1]{\hspace\labelsep
                                \normalfont\bfseries #1}
\if@titlepage
  \newenvironment{abstract}[1]{%
      \titlepage
      \null\vfil
      \begin{center}
        \bfseries \abstractname\par
      \end{center}}
      {\par\vfil\null\endtitlepage}
\else
  \newenvironment{abstract}{%
      \if@twocolumn
        \section*{\abstractname}%
      \else
        \small
        \begin{center}%
          {\bfseries \abstractname\vspace{-.5em}\vspace{\z@}}%
        \end{center}%
        \quotation
      \fi}
      {\if@twocolumn\else\endquotation\fi}
\fi
\newenvironment{verse}
               {\let\\=\@centercr
                \list{}{\itemsep      \z@
                        \itemindent   -1.5em%
                        \listparindent\itemindent
                        \rightmargin  \leftmargin
                        \advance\leftmargin 1.5em}%
                \item[]}
               {\endlist}
\newenvironment{quotation}
               {\list{}{\listparindent 1.5em%
                        \itemindent    \listparindent
                        \rightmargin   \leftmargin
                        \parsep        \z@ \@plus\p@}%
                \item[]}
               {\endlist}
\newenvironment{quote}
               {\list{}{\rightmargin\leftmargin}%
                \item[]}
               {\endlist}
\newenvironment{titlepage}
    {%
      \if@twocolumn
        \@restonecoltrue\onecolumn
      \else
        \@restonecolfalse\newpage
      \fi
      \thispagestyle{empty}%
      \if@compatibility
        \setcounter{page}{0}
      \else
        \setcounter{page}{1}%
      \fi}%
    {\if@restonecol\twocolumn \else \newpage \fi
      \setcounter{page}{1}%
    }

\setlength\arraycolsep{5\p@}
\setlength\tabcolsep{6\p@}
\setlength\arrayrulewidth{.4\p@}
\setlength\doublerulesep{2\p@}
\setlength\tabbingsep{\labelsep}
\skip\@mpfootins = \skip\footins
\setlength\fboxsep{3\p@}
\setlength\fboxrule{.4\p@}
\@addtoreset{equation}{chapter}
\renewcommand{\theequation}{\thechapter.\arabic{equation}}
\newcounter{figure}[chapter]
\renewcommand{\thefigure}{\thechapter.\@arabic\c@figure}
\def\fps@figure{tbp}
\def\ftype@figure{1}
\def\ext@figure{lof}
\def\fnum@figure{\figurename~\thefigure}
\newenvironment{figure}
               {\@float{figure}}
               {\end@float}
\newenvironment{figure*}
               {\@dblfloat{figure}}
               {\end@dblfloat}
\newcounter{table}[chapter]
\renewcommand{\thetable}{\thechapter.\@arabic\c@table}
\def\fps@table{tbp}
\def\ftype@table{2}
\def\ext@table{lot}
\def\fnum@table{\tablename~\thetable}
\newenvironment{table}
               {\@float{table}}
               {\end@float}
\newenvironment{table*}
               {\@dblfloat{table}}
               {\end@dblfloat}
\newlength\abovecaptionskip
\newlength\belowcaptionskip
\setlength\abovecaptionskip{0\p@} %{10\p@}
\setlength\belowcaptionskip{0\p@}
\long\def\@makecaption#1#2{%
  \vskip\abovecaptionskip
  \sbox\@tempboxa{#1. #2}%                
%  \sbox\@tempboxa{#1: #2}%
  \ifdim \wd\@tempboxa >\hsize
    #1. #2\par                    %       
%    #1: #2\par
  \else
    \global \@minipagefalse
    \hbox to\hsize{\hfil\box\@tempboxa\hfil}%
  \fi
  \vskip\belowcaptionskip}
\DeclareOldFontCommand{\rm}{\normalfont\rmfamily}{\mathrm}
\DeclareOldFontCommand{\sf}{\normalfont\sffamily}{\mathsf}
\DeclareOldFontCommand{\tt}{\normalfont\ttfamily}{\mathtt}
\DeclareOldFontCommand{\bf}{\normalfont\bfseries}{\mathbf}
\DeclareOldFontCommand{\it}{\normalfont\itshape}{\mathit}
\DeclareOldFontCommand{\sl}{\normalfont\slshape}{\@nomath\sl}
\DeclareOldFontCommand{\sc}{\normalfont\scshape}{\@nomath\sc}
\DeclareRobustCommand*{\cal}{\@fontswitch{\relax}{\mathcal}}
\DeclareRobustCommand*{\mit}{\@fontswitch{\relax}{\mathnormal}}
\newcommand{\@pnumwidth}{1.55em}
\newcommand{\@tocrmarg} {2.55em}
\newcommand{\@dotsep}{4.5}
\setcounter{tocdepth}{3}  



  
\newif\if@pagestyleempty       
\newcommand{\tableofcontents}{%
    \pagestyle{empty}\@pagestyleemptytrue\setlength{\parskip}{0pt}  
   \addtocontents{toc}{\noindent\contentsname\newline} 
    \if@twocolumn
      \@restonecoltrue\onecolumn
    \else
      \@restonecolfalse
    \fi
    \chapter*{\contentsname}
      %  \@mkboth{\uppercase{\contentsname}}{\uppercase{\contentsname}}%
    \@starttoc{toc}%
    \if@restonecol\twocolumn\fi \setlength{\parskip}{0pt}  
    }

\newcommand*{\l@part}[2]{%
  \ifnum \c@tocdepth >-2\relax
    \addpenalty{-\@highpenalty}%
    \addvspace{2.25em \@plus\p@}%
    \begingroup
      \setlength\@tempdima{3em}%
      \parindent \z@ \rightskip \@pnumwidth
      \parfillskip -\@pnumwidth
      {\leavevmode
       \large \bfseries #1\hfil \hbox to\@pnumwidth{\hss #2}}\par
       \nobreak
         \global\@nobreaktrue
         \everypar{\global\@nobreakfalse\everypar{}}
    \endgroup
  \fi}

\newcommand*{\l@chapter}[2]{%
  \ifnum \c@tocdepth >\m@ne
    \addpenalty{-\@highpenalty}%
    \vskip 0.0em \@plus\p@
    \setlength\@tempdima{1.5em}%
    \begingroup
      \parindent \z@ \rightskip \@pnumwidth
      \parfillskip -\@pnumwidth
      \leavevmode %\bfseries
      \advance\leftskip\@tempdima
      \hskip -\leftskip
      #1\nobreak\leaders\hbox{$\m@th \mkern \@dotsep mu.\mkern \@dotsep mu$}
\hfill \nobreak\hbox to\@pnumwidth{\hss #2}\par

      \penalty\@highpenalty
    \endgroup
  \fi}

\newcommand*{\l@section}      {\@dottedtocline{1}{1.5em}{2.3em}}
\newcommand*{\l@subsection}   {\@dottedtocline{2}{3.8em}{3.2em}}
\newcommand*{\l@subsubsection}{\@dottedtocline{3}{7.0em}{4.1em}}
\newcommand*{\l@paragraph}    {\@dottedtocline{4}{10em}{5em}}
\newcommand*{\l@subparagraph} {\@dottedtocline{5}{12em}{6em}}
\newcommand{\listoffigures}{%
    \if@twocolumn
      \@restonecoltrue\onecolumn
    \else
      \@restonecolfalse
    \fi
    \chapter*{\listfigurename
      \@mkboth{\uppercase{\listfigurename}}%
              {\uppercase{\listfigurename}}}%
    \@starttoc{lof}%
    \if@restonecol\twocolumn\fi
    }
\newcommand*{\l@figure}{\@dottedtocline{1}{1.5em}{2.3em}}
\newcommand{\listoftables}{%
    \if@twocolumn
      \@restonecoltrue\onecolumn
    \else
      \@restonecolfalse
    \fi
    \chapter*{\listtablename
      \@mkboth{\uppercase{\listtablename}}{\uppercase{\listtablename}}}%
    \@starttoc{lot}%
    \if@restonecol\twocolumn\fi
    }
\let\l@table\l@figure
\newdimen\bibindent
\bibindent=1.5em
\newcommand{\bibchnum}[1]{\gdef\@bibchnum{#1}}\gdef\@bibchnum{}
\newenvironment{thebibliography}[1]
 { \refstepcounter{chapter}\if@openright\cleardoublepage\else\clearpage\fi
   \addcontentsline{toc}{chapter}{\protect\numberline{\thechapter}\bibname}
 \clearpage \vspace*{-34pt} \begin{center} \large \bfseries \thechapter \hspace{0.7em} \bibname  \end{center} \par\par
  \list{\@biblabel{\arabic{enumiv}}}%
           {\settowidth\labelwidth{\@biblabel{#1}}%
            \leftmargin\labelwidth
            \advance\leftmargin\labelsep
            \if@openbib
              \advance\leftmargin\bibindent
              \itemindent -\bibindent
              \listparindent \itemindent
              \parsep \z@
            \fi
            \usecounter{enumiv}%
            \let\p@enumiv\@empty
            \renewcommand{\theenumiv}{\arabic{enumiv}}}%
      \if@openbib
        \renewcommand{\newblock}{\par}
      \else
        \renewcommand{\newblock}{\hskip .11em \@plus.33em \@minus.07em}%
      \fi
      \sloppy\clubpenalty4000\widowpenalty4000%
      \sfcode`\.=\@m}
     {\def\@noitemerr
       {\@latex@warning{Empty `thebibliography' environment}}%
      \endlist}                     
\newcommand{\newblock}{}
\newenvironment{theindex}
               {\if@twocolumn
                  \@restonecolfalse
                \else
                  \@restonecoltrue
                \fi
                \columnseprule \z@
                \columnsep 35\p@
                \twocolumn[\@makeschapterhead{\indexname}]%
                \@mkboth{\uppercase{\indexname}}%
                        {\uppercase{\indexname}}%
                \thispagestyle{plain}\parindent\z@
                \parskip\z@ \@plus .3\p@\relax
                \let\item\@idxitem}
               {\if@restonecol\onecolumn\else\clearpage\fi}
\newcommand{\@idxitem}  {\par\hangindent 40\p@}
\newcommand{\subitem}   {\par\hangindent 40\p@ \hspace*{20\p@}}
\newcommand{\subsubitem}{\par\hangindent 40\p@ \hspace*{30\p@}}
\newcommand{\indexspace}{\par \vskip 10\p@ \@plus5\p@ \@minus3\p@\relax}
\renewcommand{\footnoterule}{%
  \kern-3\p@
  \hrule width .4\columnwidth
  \kern 2.6\p@}
\@addtoreset{footnote}{chapter}
\long\def\@makefntext#1{%
    \parindent 1em%
    \noindent
    \hbox to 1.8em{\hss\@makefnmark}#1}
\if@suomi
 \newcommand{\contentsname}{SIS\"ALLYSLUETTELO} 
 \newcommand{\listfigurename}{KUVALUETTELO}
 \newcommand{\listtablename}{TAULUKKOLUETTELO}
 \newcommand{\bibname}{L\"AHDELUETTELO}
 \newcommand{\indexname}{INDEX}
 \newcommand{\figurename}{Kuva}
 \newcommand{\tablename}{Taulukko}
 \newcommand{\partname}{OSA}
 \newcommand{\chaptername}{LUKU}
 \newcommand{\appendixname}{LIITTEET}
 \newcommand{\abstractname}{TIIVISTELM\"A}
 \newcommand{\prefacename}{ALKULAUSE}
 \newcommand{\@symbolsname}{LYHENTEIDEN JA MERKKIEN SELITYKSET}
 \newcommand{\today}{\ifcase\month\or
  Tammikuu\or Helmikuu\or Maaliskuu\or Huhtikuu\or Toukokuu\or Kes\"akuu\or
  Hein\"akuu\or Elokuu\or Syyskuu\or Lokakuu\or Marraskuu\or Joulukuu\fi
  \space\number\day, \number\year}
\else
 \newcommand{\contentsname}{CONTENTS} 
 \newcommand{\listfigurename}{LIST of FIGURES}
 \newcommand{\listtablename}{LIST of TABLES}
 \newcommand{\bibname}{BIBLIOGRAPHY}
 \newcommand{\indexname}{INDEX}
 \newcommand{\figurename}{Figure}
 \newcommand{\tablename}{Table}
 \newcommand{\partname}{PART}
 \newcommand{\chaptername}{CHAPTER}
 \newcommand{\appendixname}{APPENDIX}
 \newcommand{\abstractname}{ABSTRACT}
 \newcommand{\prefacename}{PREFACE}
 \newcommand{\@symbolsname}{LIST OF SYMBOLS AND ABBREVIATIONS}
 \newcommand{\today}{\ifcase\month\or
  January\or February\or March\or April\or May\or June\or
  July\or August\or September\or October\or November\or December\fi
  \space\number\day, \number\year}
\fi

\setlength\columnsep{10\p@}
\setlength\columnseprule{0\p@}
\pagestyle{headings}                                 
\pagenumbering{arabic}      % Arabic page numbers
\if@twoside
\else
  \raggedbottom
\fi
\if@twocolumn
  \twocolumn
  \sloppy
  \flushbottom
\else
  \onecolumn
\fi


\newcommand{\abstractpage}[4]{%  %bold info,regular info, text, keywords
\addtocontents{toc}{\noindent\abstractname\newline}
\pagestyle{empty}\@pagestyleemptytrue
\clearpage\vspace*{-14pt}
\hspace{-23.32pt} 
%\noindent 
\textbf{ #1}\ #2\par\par\par
\begin{center}\textbf{{\large \abstractname}}\end{center}
\begin{bfseries} #3 \par
\noindent Keywords:\ #4
\end{bfseries}}
\newcommand{\abstractother}[4]{% abstract in other language  %bold info,regular info, text, keywords
\if@suomi 
 \newcommand{\@absname}{ABSTRACT}
\else
 \newcommand{\@absname}{TIIVISTELM\"A}
\fi
\addtocontents{toc}{\noindent\@absname\newline}
\pagestyle{empty}\@pagestyleemptytrue
\clearpage\vspace*{-14pt}
\noindent \textbf{#1}\ #2\par\par\par
\begin{center}\textbf{{\large \@absname}}\end{center}
\begin{bfseries} #3 \par
\noindent Avainsanat:\ #4
\end{bfseries}}

%\ifsymbolspage
\newcommand{\prefacepage}[1]{%
\ifsymbolspage
\addtocontents{toc}{\noindent\prefacename \newline}
\else
\addtocontents{toc}{\noindent\prefacename \par}
\fi
\pagestyle{empty}\@pagestyleemptytrue
\clearpage\vspace*{-34pt}
\begin{center}\textbf{{\large\prefacename}}\end{center}\par\par
#1}
%\else
%\newcommand{\prefacepage}[1]{%
%\pagestyle{empty}\@pagestyleemptytrue
%\addtocontents{toc}{\noindent\prefacename}
%\clearpage\vspace*{-34pt}
%\begin{center}\textbf{{\large\prefacename}}\end{center}\par\par
%#1}
%\fi
\newif\ifsymbolspage
\newcommand{\symbolspage}[1]{%
\symbolspagetrue
\pagestyle{empty}\@pagestyleemptytrue
\addtocontents{toc}{\noindent\@symbolsname\par}  %par prevents problems when addtocontentsline is after it (first chapter)
%https://tex.stackexchange.com/questions/139620/missing-item-with-addtocontents-before-section
\clearpage\vspace*{-34pt}
\begin{center}\textbf{{\large \@symbolsname}}\end{center}\par\par
#1}


%%
%% End of file `dithesis.cls'.






