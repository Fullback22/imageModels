#include "ProbabilitiesFieldWidget.h"

ProbabilitiesFieldWidget::ProbabilitiesFieldWidget(QWidget *parent)
	: QScrollArea(parent)
{
	ui.setupUi(this);

	gridLayout = new QGridLayout();
	contentWidget = new QWidget();
	contentWidget->setLayout(gridLayout);
	setWidgetResizable(true);
	setWidget(contentWidget);
}

ProbabilitiesFieldWidget::~ProbabilitiesFieldWidget()
{
}

void ProbabilitiesFieldWidget::resize(size_t const newSize)
{
	if (newSize > fieldSize)
	{
		le_field.resize(newSize);
		labelsColsPosition.resize(newSize);
		labelsRowsPosition.resize(newSize);
		for (size_t i{ fieldSize }; i < newSize; ++i)
		{
			labelsColsPosition[i] = new QLabel(QString::number(i + 1));
			labelsColsPosition[i]->setAlignment(Qt::AlignCenter);
			labelsColsPosition[i]->setMaximumWidth(30);
			labelsRowsPosition[i] = new QLabel(QString::number(i + 1));
			labelsRowsPosition[i]->setAlignment(Qt::AlignCenter);
			labelsRowsPosition[i]->setMaximumWidth(30);

			gridLayout->addWidget(labelsRowsPosition[i], 0, i + 1);
			gridLayout->addWidget(labelsColsPosition[i], i + 1, 0);
			
			le_field[i].resize(newSize);
			for (size_t j{ }; j < fieldSize; ++j)
			{
				addLineEdit(j, i);
			}
		}

		for (size_t i{}; i < newSize; ++i)
		{
			le_field[i].resize(newSize);
			for (size_t j{ fieldSize }; j < newSize; ++j)
			{
				addLineEdit(j, i);
			}
		}
	}
	else if (newSize < fieldSize)
	{
		for (size_t i{ 0 }; i < newSize; ++i)
		{
			for (size_t j{ newSize}; j < fieldSize; ++j)
			{
				le_field[i][j]->hide();
				delete le_field[i][j];
				le_field[i][j] = nullptr;
			}
			le_field[i].resize(newSize);
		}
		for (size_t i{ newSize }; i < fieldSize; ++i)
		{
			labelsColsPosition[i]->hide();
			delete labelsColsPosition[i];
			labelsColsPosition[i]=nullptr;

			labelsRowsPosition[i]->hide();
			delete labelsRowsPosition[i];
			labelsRowsPosition[i] = nullptr;

			for (size_t j{ 0 }; j < fieldSize; ++j)
			{
				le_field[i][j]->hide();
				delete le_field[i][j];
				le_field[i][j] = nullptr;
			}
		}
		le_field.resize(newSize);
	}
	fieldSize = newSize;
}

bool ProbabilitiesFieldWidget::fieldIsCorrect() const
{
	if (quantityIncorectLe == 0)
		return true;
	return false;
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
		if (ok && (value <= 0 || value > 100))
		{
			if (le_field[y][x]->styleSheet() == "")
			{
				++quantityIncorectLe;
				emit fieldChanged();
			}
			le_field[y][x]->setText("");
			le_field[y][x]->setStyleSheet("border: 2px solid red;");
		}
		else if (ok)
		{
			if (le_field[y][x]->styleSheet() != "")
			{
				--quantityIncorectLe;
				emit fieldChanged();
			}
			le_field[y][x]->setStyleSheet("");
		}
		});
	gridLayout->addWidget(le_field[y][x], y + 1, x + 1);
}

