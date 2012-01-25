#include <QtGui>
#include <QWebView>

#include "webslidesapp.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	if ( QApplication::arguments().size() < 3 ) {
		qDebug() << "Usage: web2slides <html file> <slide count> [WIDTHxHEIGHT]";
		return -1;
	}
	QString file = QApplication::arguments()[1];

	QUrl url(file);
	if ( url.scheme().isEmpty() ) {
		url = QUrl::fromLocalFile(QDir::currentPath()).resolved(url);
	}

	if ( url.isLocalFile() && !QFileInfo(url.toLocalFile()).isFile() ) {
		qDebug() << "Unable to open" << QApplication::arguments()[1];
		return -1;
	}

	bool ok;
	int pages = QApplication::arguments()[2].toInt(&ok);
	if ( !ok ) {
		qDebug() << "Invalid page count" << QApplication::arguments()[2];
		return -1;
	}


	// Parse optional resolution argument
	QSize size = QSize(1920, 1080);
	if ( QApplication::arguments().size() == 4 ) {
		QStringList resolution = QApplication::arguments()[3].split('x');
		if ( resolution.size() != 2 ) {
			qDebug() << "Invalid resolution value";
			return -1;
		}

		int width = resolution[0].toInt(&ok);
		if (!ok) {
			qDebug() << "Invalid resolution width";
			return -1;
		}

		int height = resolution[1].toInt(&ok);
		if (!ok) {
			qDebug() << "Invalid resolution height";
			return -1;
		}

		size = QSize(width, height);
	}
	
	QWebView w;
	w.setGeometry( QRect(QPoint(0, 0), size) );
	w.page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
	w.page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
	w.load(url);

	WebSlidesApp slides(&w);
	slides.setPageCount(pages),
	slides.setPageSize(size);
	return app.exec();
}
