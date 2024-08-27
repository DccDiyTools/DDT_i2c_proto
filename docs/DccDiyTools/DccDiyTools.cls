% !TeX encoding = UTF-8
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Daniel Bahn Master Document
% LaTeX Class
% Version 0.1 (Jun 24, 2022)
% 
% Author:
% Daniel (daniel.vilas@gmail.com)
%
% License:
% CC BY-NC-SA 4.0 (https://creativecommons.org/licenses/by-nc-sa/4.0/)
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%----------------------------------------------------------------------------------------
%	CLASS CONFIGURATION
%----------------------------------------------------------------------------------------

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{DccDiyTools/DccDiyTools}[2022/06/24 Dcc Diy Tools Master Document Class v0.1]

\RequirePackage[dvipsnames,table]{xcolor}
\usepackage[dvi]{totpages}
\usepackage{etoolbox}
\usepackage{graphicx}
\usepackage{float}
\usepackage{tikz}
\usetikzlibrary{fit}
\RequirePackage[european]{circuitikz}
\RequirePackage{siunitx}
\usetikzlibrary{patterns.meta}
\usepackage{tcolorbox}
\usepackage{tabularx}
\usepackage{multirow}
\usepackage{makecell}
\DeclareOption{english}{\AtEndOfClass{\main@language{english}} \PassOptionsToPackage{\CurrentOption}{babel}}
\DeclareOption{spanish}{\AtEndOfClass{\main@language{spanish}} \PassOptionsToPackage{\CurrentOption}{babel}}

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
\ProcessOptions\relax
\LoadClass{article}

\RequirePackage[]{babel}
\usepackage[oneside]{sidenotes}
\RequirePackage{hyperref}
\usepackage{listings}


%\hypersetup{
%    colorlinks=true,
%    linkcolor=blue,
%    filecolor=magenta,      
%    urlcolor=cyan,
%    pdftitle={Overleaf Example},
%    pdfpagemode=FullScreen,
%    }
%%---------------------
%% Datos para el Documento DanielBahn
%%---------------------
\newcommand{\dbHeaderTitle}[1]{\renewcommand{\dbHeaderTitle}{#1}}
\newcommand{\dbType}[1]{\renewcommand{\dbType}{#1}}
\newcommand{\dbCode}[1]{\renewcommand{\dbCode}{#1}}
\newcommand{\dbDate}[1]{\renewcommand{\dbDate}{#1}}
\newcommand{\dbStatus}[1]{\renewcommand{\dbStatus}{#1}}
\newcommand{\dbVersion}[1]{\renewcommand{\dbVersion}{#1}}
\newcommand{\subtitle}[1]{\renewcommand{\subtitle}{#1}}
\newcommand{\dbImage}[1]{\renewcommand{\dbImage}{#1} \settoggle{dbImagePresent}{true}}

%%---------------------
%% Configuracion de la pagina
%%---------------------
%\settoggle{dbImagePresent}{true}
\newtoggle{dbImagePresent}
\settoggle{dbImagePresent}{false}
%\DeclareOption{unnumberedsections}{\settoggle{unnumberedsections}{true}} % Set the class option toggle if the class option was used in the template


\usepackage[
    top=2cm,
    bottom=2cm,
    left=1cm,
    right=5.25cm,
    marginparwidth=4.25cm,
    marginparsep=0.5cm,
    footskip=1.5cm,
    headsep=0.8cm,
    headheight=1cm,
    %showframe 
]{geometry}

\newenvironment{pagcompleta}{
    \begin{adjustwidth}{}{\dimexpr-\marginparwidth-\marginparsep\relax}
        }{
    \end{adjustwidth}
}

%----------------------------------------------------------------------------------------
%	FONTS
%----------------------------------------------------------------------------------------

\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}

\usepackage{mathpazo}
\usepackage[leqno]{amsmath}
\numberwithin{equation}{section}

\usepackage[sfdefault]{plex-sans}
\usepackage{plex-serif}
\usepackage{plex-mono}

\setlength{\parskip}{6pt}

\usepackage{pdflscape}

%%---------------------
%% Titulo, nueva pagina y personalizacion
%%---------------------
\let\dbOldMaketitle\@maketitle

\makeatletter
\def\@maketitle{%
    %   \dbOldMaketitle
    % Suppress headers and footers on this page

    \begin{pagcompleta}
        \thispagestyle{empty}
        \tikz[remember picture,overlay] \node[opacity=0.3,inner sep=0pt] at ([xshift=\marginparsep/2]current page.center){\includegraphics[width=10cm]{DccDiyTools/Fondo.png}};
        \centering
        \hfill\includegraphics[height=2cm]{DccDiyTools/LogoLargo.png}
        \parbox[b][2cm][t]{2.5cm}{
            \vfill
            \parbox[b][0.25cm][c]{2.5cm}{ }
            \parbox[b][0.5cm][c]{2.5cm}{
                \centering \dbType
            }
            \parbox[b][0.5cm][c]{2.5cm}{
                \centering {\Large\textbf{\dbDate-\dbCode}}
            }
            \parbox[b][0.5cm][c]{2.5cm}{
                \centering \dbStatus \ v\dbVersion
            }
            \parbox[b][0.25cm][c]{2.5cm}{ }

        }\par
        %\setlength{\parindent}{-100pt}
        \vspace{10\baselineskip}
        \large \dbType \ {\textbf{\dbDate-\dbCode}}\par
        {\fontsize{60pt}{64pt}\usefont{T1}{qzc}{m}{it}\@title \par}
        {\fontsize{40pt}{42pt}\selectfont\subtitle \par}

        {\Large\fontseries{l}\selectfont{\@author}\par}
        {\small\usefont{T1}{MontserratAlternates-TOsF}{b}{n}(\dbStatus \ v\dbVersion)}\par

        \iftoggle{dbImagePresent}{ % Conditional logic for the unnumbered sections class options
            \vspace{5\baselineskip}
            \includegraphics{\dbImage}
        }{

        }
    \end{pagcompleta}

    %\dbOldMaketitle

    \newpage
    \thispagestyle{fancy}
    \vspace*{\fill}
    \doclicenseThis
    \pagestyle{fancy}
    %\newpage
}
\makeatother


\makeatletter
\RenewDocumentCommand\sidenotetext{o o +m}{%      
    \IfNoValueOrEmptyTF{#1}{%
        \@sidenotes@placemarginal{#2}{\textsuperscript{\thesidenote}\footnotesize#3}
        \refstepcounter{sidenote}%
    }{
        \@sidenotes@placemarginal{#2}{\textsuperscript{#1}\footnotesize#3}
    }
}
\makeatother


%----------------------------------------------------------------------------------------
%	Cabecera y Pie
%----------------------------------------------------------------------------------------

\usepackage{fancyhdr}
\pagestyle{fancy}

\renewcommand{\headrulewidth}{1.5pt}
\fancyhf{}

\fancyhead[L]{\dbType \ \dbDate-\dbCode \ (\dbStatus)}
\fancyhead[C]{\dbHeaderTitle\  v\dbVersion}
\fancyhead[R]{\includegraphics[height=0.75cm]{DccDiyTools/LogoLargo.png}}
\fancyfoot[L]{} % Left footer
\fancyfoot[C]{\thepage/\ref{TotPages}} % Center footer
\fancyfoot[R]{} % Right footer


\usepackage[framemethod=TikZ]{mdframed}
\definecolor{codegreen}{rgb}{0,0.6,0}
\definecolor{codegray}{rgb}{0.5,0.5,0.5}
\definecolor{codepurple}{rgb}{0.58,0,0.82}
\definecolor{codebg}{rgb}{0.95,0.95,0.92}
\definecolor{codered}{rgb}{0.65,0.08,0.26}

\newmdenv[outerlinewidth = 1,%
    roundcorner = 10pt,
    leftmargin = 20,
    rightmargin = 20,
    backgroundcolor = codebg,
    outerlinecolor = blue!70!black,
    innertopmargin = \topskip,
    splittopskip = \topskip,
]{mdCode}

\lstdefinestyle{cppstyle}{
    %backgroundcolor=\color{backcolour},
    commentstyle=\color{codegreen}\ttfamily,
    keywordstyle=\color{codepurple}\ttfamily,
    numberstyle=\tiny\color{codegray},
    stringstyle=\color{codered}\ttfamily,
    basicstyle=\ttfamily\footnotesize,
    breakatwhitespace=false,
    breaklines=true,
    captionpos=b,
    keepspaces=true,
    numbers=left,
    numbersep=5pt,
    showspaces=false,
    showstringspaces=false,
    showtabs=false,
    tabsize=2,
    morekeywords={byte}
}

%basicstyle=\ttfamily,
%morecomment=[l][\color{magenta}]{\#}