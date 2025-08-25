#include "ProbabilitiesFieldWidget.h"

ProbabilitiesFieldWidget::ProbabilitiesFieldWidget(QWidget *parent)
	: QScrollArea(parent)
{
	ui.setupUi(this);

	contentWidget = new QWidget();
	mainLayout = new QVBoxLayout();
	contentWidget->setLayout(mainLayout);
	setWidget(contentWidget);

	gridLayout = new QGridLayout();
	mainLayout->addLayout(gridLayout);

	buttonLayout = new QHBoxLayout();
	mainLayout->addLayout(buttonLayout);

	pb_random = new QPushButton(QString::fromLocal8Bit("Случайно"), this);
	pb_random->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	buttonLayout->addWidget(pb_random);
	

	setWidgetResizable(true);
	connect(pb_random, &QPushButton::clicked, this, &ProbabilitiesFieldWidget::slot_randomGenerate);
}

ProbabilitiesFieldWidget::~ProbabilitiesFieldWidget()
{
}

void ProbabilitiesFieldWidget::resize(const QSize& newSize)
{
	if (newSize.height() > fieldSize.height())
	{
		addRows(newSize);
	}
	else if (newSize.height() < fieldSize.height())
	{
		removeRows(newSize);
	}
	fieldSize.setHeight(newSize.height());
	if (newSize.width() > fieldSize.width())
	{
		addCols(newSize.width());
	}
	else if (newSize.width() < fieldSize.width())
	{
		removeCols(newSize.width());
	}
	fieldSize.setWidth(newSize.width());
}

bool ProbabilitiesFieldWidget::fieldIsCorrect() const
{
	if (quantityIncorectLe == 0)
		return true;
	return false;
}

void ProbabilitiesFieldWidget::randomInit()
{
	std::random_device rd{};
	std::mt19937 generator{ rd() };
	std::uniform_int_distribution<int> fieldDis{ 0,100 };
	for (size_t i{}; i < fieldSize.height(); ++i)
	{
		for (size_t j{}; j < fieldSize.width(); ++j)
		{
			le_field[i][j]->setText(QString::number(fieldDis(generator)));
		}
	}
}

void ProbabilitiesFieldWidget::oneInit()
{
	for (size_t i{}; i < fieldSize.height(); ++i)
	{
		for (size_t j{}; j < fieldSize.width(); ++j)
		{
			le_field[i][j]->setText(QString::number(1));
		}
	}
}

void ProbabilitiesFieldWidget::diagonalInit(int const diagonalValue)
{
	for (size_t i{}; i < fieldSize.height(); ++i)
	{
		for (size_t j{}; j < fieldSize.width(); ++j)
		{
			if (i == j)
			{
				le_field[i][j]->setText(QString::number(diagonalValue));
			}
			else {
				le_field[i][j]->setText(QString::number(1));
			}
		}
	}
}

void ProbabilitiesFieldWidget::getField(std::vector<std::vector<unsigned int>>& outField)
{
	outField.resize(fieldSize.height());
	for (size_t i{}; i < fieldSize.height(); ++i)
	{
		outField[i].resize(fieldSize.width());
		for (size_t j{}; j < fieldSize.width(); ++j)
		{
			outField[i][j] = static_cast<unsigned int>(le_field[i][j]->text().toInt());
			unsigned int d = static_cast<unsigned int>(le_field[i][j]->text().toInt());
		}
	}
}

void ProbabilitiesFieldWidget::addLineEdit(size_t const x, size_t const y)
{
	le_field[y][x] = new QLineEdit(this);
	le_field[y][x]->setMaximumWidth(30);
	le_field[y][x]->setValidator(&validator);
	le_field[y][x]->setText("1");
	connect(le_field[y][x], &QLineEdit::textChanged, [=]() {
		bool ok{};
		int value{ le_field[y][x]->text().toInt(&ok) };
		if (ok && (value < 0 || value > 100))
		{
			if (le_field[y][x]->styleSheet() == "")
			{
				++quantityIncorectLe;
			}
			le_field[y][x]->setText("");
			le_field[y][x]->setStyleSheet("border: 2px solid red;");
		}
		else if (ok)
		{
			if (le_field[y][x]->styleSheet() != "")
			{
				--quantityIncorectLe;
			}
			le_field[y][x]->setStyleSheet("");
			emit fieldValuesChanged();
		}
		});
	gridLayout->addWidget(le_field[y][x], y + 1, x + 1);
}

void ProbabilitiesFieldWidget::addCols(size_t const newCols)
{
	labelsColsPosition.resize(newCols);
	for (int i{ fieldSize.width() }; i < newCols; ++i)
	{
		labelsColsPosition[i] = new QLabel(QString::number(i + 1));
		labelsColsPosition[i]->setAlignment(Qt::AlignCenter);
		labelsColsPosition[i]->setMaximumWidth(30);

		gridLayout->addWidget(labelsColsPosition[i], i + 1, 0);
	}

	for (int i{}; i < fieldSize.height(); ++i)
	{
		le_field[i].resize(newCols);
		for (int j{ fieldSize.width() }; j < newCols; ++j)
		{
			addLineEdit(j, i);
		}
	}
}

void ProbabilitiesFieldWidget::removeCols(size_t const newCols)
{
	for (int i{ 0 }; i < fieldSize.height(); ++i)
	{
		for (size_t j{ newCols }; j < fieldSize.width(); ++j)
		{
			le_field[i][j]->hide();
			delete le_field[i][j];
			le_field[i][j] = nullptr;
		}
		le_field[i].resize(newCols);
	}

	for (size_t i{ newCols }; i < fieldSize.width(); ++i)
	{
		labelsColsPosition[i]->hide();
		delete labelsColsPosition[i];
		labelsColsPosition[i] = nullptr;
	}

}

void ProbabilitiesFieldWidget::addRows(const QSize& newSize)
{
	le_field.resize(newSize.height());
	labelsRowsPosition.resize(newSize.height());
	for (int i{ fieldSize.height() }; i < newSize.height(); ++i)
	{
		labelsRowsPosition[i] = new QLabel(QString::number(i + 1));
		labelsRowsPosition[i]->setAlignment(Qt::AlignCenter);
		labelsRowsPosition[i]->setMaximumWidth(30);

		gridLayout->addWidget(labelsRowsPosition[i], 0, i + 1);

		if (newSize.width() >= fieldSize.width())
		{
			le_field[i].resize(fieldSize.width());
			for (int j{ }; j < fieldSize.width(); ++j)
			{
				addLineEdit(j, i);
			}
		}
	}
}

void ProbabilitiesFieldWidget::removeRows(const QSize& newSize)
{

	for (int i{ newSize.height() }; i < fieldSize.height(); ++i)
	{
		labelsRowsPosition[i]->hide();
		delete labelsRowsPosition[i];
		labelsRowsPosition[i] = nullptr;

		for (int j{}; j < fieldSize.width(); ++j)
		{
			le_field[i][j]->hide();
			delete le_field[i][j];
			le_field[i][j] = nullptr;
		}
	}
	le_field.resize(newSize.height());
}

void ProbabilitiesFieldWidget::slot_randomGenerate()
{
	randomInit();
}

