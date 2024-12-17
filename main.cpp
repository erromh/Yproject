#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "CourseLib.h"

class MainComponent : public juce::Component
{
  public:
    MainComponent()
    {
        // Настраиваем текстовые поля и выпадающий список
        label1.setColour(juce::Label::textColourId, juce::Colours::black);
        label1.setText("Task Name:", juce::dontSendNotification);
        addAndMakeVisible(label1);
        addAndMakeVisible(textField1);

        label2.setColour(juce::Label::textColourId, juce::Colours::black);
        label2.setText("Execution Time:", juce::dontSendNotification);
        addAndMakeVisible(label2);
        addAndMakeVisible(textField2);

        comboBox.addItem("Round Robin", 1);
        comboBox.addItem("FCFS", 2);
        comboBox.setSelectedId(1);
        addAndMakeVisible(comboBox);

        // Настраиваем кнопки
        button1.setButtonText("Add Task");
        button1.onClick = [this]() { handleAddProcess(); };
        addAndMakeVisible(button1);

        button2.setButtonText("Execute Tasks");
        button2.onClick = [this]() { handleExecuteProcesses(); };
        addAndMakeVisible(button2);

        infoLabel.setColour(juce::Label::backgroundColourId, juce::Colours::lightgrey);
        infoLabel.setColour(juce::Label::textColourId, juce::Colours::black);
        infoLabel.setJustificationType(juce::Justification::topLeft);
        infoLabel.setFont(juce::Font(14.0f));
        addAndMakeVisible(infoLabel);

        setSize(800, 600);
    }

    void resized() override
    {
        label1.setBounds(20, 20, 200, 30);
        textField1.setBounds(20, 50, 200, 30);

        label2.setBounds(20, 90, 200, 30);
        textField2.setBounds(20, 120, 200, 30);

        comboBox.setBounds(20, 160, 200, 30);

        button1.setBounds(20, 210, 120, 40);
        button2.setBounds(150, 210, 120, 40);

        infoLabel.setBounds(20, 280, 760, 620);
    }

  private:
    CourseLib courseLib;
    int processId = 1;
    int characterLenth = 990;

    // Добавление процесса
    void handleAddProcess()
    {
        // Проверка заполненности полей
        juce::String warnings;

        if (textField1.getText().isEmpty())
        {
            warnings += "Task Name cannot be empty.\n";

            if (infoLabel.getText().length() > characterLenth)
            {
                infoLabel.setText("", juce::dontSendNotification);
            }
        }

        if (textField2.getText().isEmpty())
        {
            warnings += "Execution Time cannot be empty.\n";

            if (infoLabel.getText().length() > characterLenth)
            {
                infoLabel.setText("", juce::dontSendNotification);
            }
        }

        if (!warnings.isEmpty())
        {
            juce::String currentText = infoLabel.getText();
            currentText += warnings;
            infoLabel.setText(currentText, juce::dontSendNotification);
            return;
        }

        std::string taskName = textField1.getText().toStdString();
        int burstTime = std::stoi(textField2.getText().toStdString());
        std::string priority = (comboBox.getText() == "Round Robin") ? "high" : "low";

        courseLib.addProcess(processId++, burstTime, priority, taskName);

        juce::String currentText = infoLabel.getText();
        currentText += "Added Task: '" + juce::String(taskName) + "' | Priority: " + juce::String(priority) +
                       " | Time: " + juce::String(burstTime) + "\n";

        infoLabel.setText(currentText, juce::dontSendNotification);

        if (infoLabel.getText().length() >= characterLenth)
        {
            infoLabel.setText("", juce::dontSendNotification);
        }
    }

    void handleExecuteProcesses()
    {
        juce::String warnings;

        // Проверяем, заполнены ли поля
        if (textField1.getText().isEmpty() || textField2.getText().isEmpty())
        {
            warnings = "Cannot execute processes: Missing data.\n";
            juce::String currentText = infoLabel.getText();
            currentText += warnings;
            infoLabel.setText(currentText, juce::dontSendNotification);
            return;
        }

        juce::String currentText = infoLabel.getText();
        currentText += "\nExecuting Round Robin Tasks:\n";

        infoLabel.setText(currentText, juce::dontSendNotification);

        if (infoLabel.getText().length() >= 1200)
        {
            infoLabel.setText("", juce::dontSendNotification);
        }

        courseLib.executeRoundRobin(5, [this](const std::string &output) {
            juce::String currentText = infoLabel.getText();
            currentText += juce::String(output) + "\n";
            infoLabel.setText(currentText, juce::dontSendNotification);
        });

        currentText = infoLabel.getText();
        currentText += "\nExecuting FCFS Tasks:\n";
        infoLabel.setText(currentText, juce::dontSendNotification);

        courseLib.executeFCFS([this](const std::string &output) {
            juce::String currentText = infoLabel.getText();
            currentText += juce::String(output) + "\n";
            infoLabel.setText(currentText, juce::dontSendNotification);
        });
    }

    juce::Label label1, label2;
    juce::TextEditor textField1, textField2;
    juce::ComboBox comboBox;
    juce::TextButton button1, button2;
    juce::Label infoLabel;
};

// Основное окно приложения
class MainWindow : public juce::DocumentWindow
{
  public:
    MainWindow() : DocumentWindow("Task Manager", juce::Colours::lightgrey, DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), true);

        setResizable(true, true);
        centreWithSize(850, 800);
        setVisible(true);
    }

    void closeButtonPressed() override
    {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }
};

class SimpleApp : public juce::JUCEApplication
{
  public:
    const juce::String getApplicationName() override
    {
        return "Task Manager";
    }

    const juce::String getApplicationVersion() override
    {
        return "1.0.0";
    }

    void initialise(const juce::String &) override
    {
        // Создаём основное окно
        mainWindow.reset(new MainWindow());
    }

    void shutdown() override
    {
        // Удаляем окно перед завершением приложения
        mainWindow = nullptr;
    }

  private:
    std::unique_ptr<MainWindow> mainWindow;
};

// Макрос для запуска приложения
START_JUCE_APPLICATION(SimpleApp)
