#include "webslidesapp.h"


WebSlidesApp::WebSlidesApp(QWebView *w, QObject *parent)
:QObject(parent), m_current_page(1), m_webview(w), m_initialised(false)
{
	m_printer = new QPrinter(QPrinter::HighResolution);
	m_painter = new QPainter();
	connect(w, SIGNAL(loadFinished(bool)),
			this, SLOT(webviewFinishedLoading(bool)) );
}

void WebSlidesApp::webviewFinishedLoading(bool ok)
{
	if ( !ok ) {
		QApplication::quit();
	}

	if (!m_initialised) {
		m_printer->setResolution(95);
		m_printer->setOutputFileName("html.pdf");
		m_printer->setFullPage(true);
		m_printer->setPageMargins(0,0,0,0, QPrinter::DevicePixel);
		m_printer->setPaperSize( 2*m_pageSize, QPrinter::DevicePixel);
		m_painter->begin(m_printer);
		m_painter->scale(2,2);
		m_painter->setRenderHints(QPainter::Antialiasing);
		//m_painter->setRenderHints(QPainter::TextAntialiasing, false);
		
		m_initialised = true;
	}

	printPage();
}

void WebSlidesApp::printPage()
{
	qDebug() << "Printing page" << m_current_page;

	m_webview->render(m_painter);

	if ( m_current_page == m_pageCount ) {
		m_painter->end();
		QApplication::quit();
		return;
	}
	m_current_page++;
	m_printer->newPage();


	QKeyEvent ev_press(QEvent::KeyPress, Qt::Key_PageDown, Qt::NoModifier);
	QApplication::sendEvent(m_webview, &ev_press);
	QKeyEvent ev_rel(QEvent::KeyRelease, Qt::Key_PageDown, Qt::NoModifier);
	QApplication::sendEvent(m_webview, &ev_rel);

	QTimer::singleShot(2000, this, SLOT(printPage()));
}


