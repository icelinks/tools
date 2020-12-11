\ProvidesClass{resume}[Resume class by icelinks(fh)]
\NeedsTeXFormat{LaTeX2e}

\LoadClass[10pt]{ctexart}

\setlength\parindent{0pt} % 去除段首缩进

\RequirePackage[a4paper, hmargin=1.5cm, vmargin=1.75cm]{geometry} % 设置纸张

\RequirePackage[nobottomtitles*]{titlesec}

%----------------------------------------------------------------------------------------
% 字体
%----------------------------------------------------------------------------------------

\usepackage{fontspec}

\newfontfamily{\FA}[Path=fonts/]{FontAwesome}
\input{fonts/fontawesomesymbols-xeluatex.tex}

%----------------------------------------------------------------------------------------
% 颜色
%----------------------------------------------------------------------------------------

\RequirePackage[usenames, svgnames]{xcolor}

\definecolor{text}{HTML}{2b2b2b} % 黑色
\definecolor{headings}{HTML}{701112} % 暗红色
\definecolor{shade}{HTML}{F5DD9D} % 桃红色

\color{text}

%----------------------------------------------------------------------------------------
% 页眉页脚
%----------------------------------------------------------------------------------------

\RequirePackage{fancyhdr}

\pagestyle{fancy}

\fancyhf{}

\renewcommand{\headrulewidth}{0pt}

%----------------------------------------------------------------------------------------
% 段落
%----------------------------------------------------------------------------------------

\usepackage[nobottomtitles*]{titlesec}

\renewcommand{\bottomtitlespace}{0.1\textheight}

\titleformat{\section}{\color{headings}\LARGE\raggedright}{}{0em}{}[\color{black}\titlerule]

\titlespacing{\section}{0pt}{0pt}{8pt}

%----------------------------------------------------------------------------------------
% 开头简介
%----------------------------------------------------------------------------------------

\newcommand{\info}[5]{
	\parbox[t][0.12\textheight][c]{0.45\linewidth}{
		\vspace{-0.04\textheight}
		\centering
		{\sffamily\Huge #1}\\ % 名字
	}
	\parbox[t][0.12\textheight][c]{0.45\linewidth}{
		\vspace{-0.04\textheight}
		\flushright
		\colorbox{shade}{
			\begin{tabular}{l|l}
				\raisebox{0pt}{\faBirthdayCake} & #2 \faMars\\ % 生日 & 男性
				\raisebox{0pt}{\faPhone} & #3 \\ % 电话
				\raisebox{0pt}{\small\faEnvelope} & #4 \\ % 邮箱
				\raisebox{0pt}{\small\faGraduationCap} & #5 \\ % 学历
			\end{tabular}
		}
	}
}

%----------------------------------------------------------------------------------------
% 教育经历
%----------------------------------------------------------------------------------------

\RequirePackage{tabularx}
\RequirePackage{array}

\newcommand{\educationinfo}[3]{
	\begin{tabularx}{0.99\linewidth}
	{>{\raggedright}X>{\centering}X>{\raggedleft}X}
		\emph{#1} & \textbf{#2} & \textbf{#3}
	\end{tabularx} % 时间 学校 学位
}

\newcommand{\educationitembegin}[1]{
	\begin{itemize}
}

\newcommand{\educationitem}[2]{
	\item \textbf{#1}：#2 % item名称 item内容
}

\newcommand{\educationitemend}[1]{
	\end{itemize}
}

%----------------------------------------------------------------------------------------
% 工作经历
%----------------------------------------------------------------------------------------

\newcommand{\workinfo}[3]{
	\begin{tabularx}{0.99\linewidth}
	{>{\raggedright}X>{\centering}X>{\raggedleft}X}
		\emph{#1} & \textbf{#2} & \textbf{#3}
	\end{tabularx} % 工作时间 公司部门 职位
}

\newcommand{\workitembegin}[1]{
	\begin{description}
		\item[#1] % 工作内容概述
	\end{description}
	\begin{itemize}	
}

\newcommand{\workitem}[1]{
	\item #1 % 工作内容子项
}

\newcommand{\workitemend}[1]{
	\end{itemize}
}

%----------------------------------------------------------------------------------------
% 项目经历
%----------------------------------------------------------------------------------------

\newcommand{\projectitembegin}[1]{
	\begin{description}
		\item[#1] % 项目名称
	\end{description}
	\begin{itemize}	
}

\newcommand{\projectitem}[1]{
	\item #1 % 项目内容子项
}

\newcommand{\projectitemend}[1]{
	\end{itemize}
}

%----------------------------------------------------------------------------------------
% 技能
%----------------------------------------------------------------------------------------

\newcommand{\skillitembegin}[1]{
	\begin{itemize}	
}

\newcommand{\skillitem}[1]{
	\item #1 % 掌握技能子项
}

\newcommand{\skillitemend}[1]{
	\end{itemize}
}

%----------------------------------------------------------------------------------------
% 长度获取宏
%----------------------------------------------------------------------------------------

\newcommand{\length}[1]{
	{\count0=0 \getlength#1\end \number\count0}
}

\newcommand{\getlength}[1]{
	\ifx#1\end \let\next=\relax
	\else\advance\count0 by1 \let\next=\getlength\fi \next
}