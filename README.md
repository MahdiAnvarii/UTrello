# UTrello - Task & Event Scheduler  
![UTrelloPic](https://drive.google.com/uc?export=view&id=10GTguiuto93vsm8TyHQNkB093Uyds2dG)

## 📝 Repository Description
UTrello is a powerful task and event management system designed to help users organize their time effectively.
Originally a command-line tool in C++, UTrello has evolved into a web-based application with a user-friendly interface and robust scheduling logic.
- ✅ User authentication
- 📅 Date/time management
- 🔄 Support for periodic events (daily/weekly/monthly)
- 🤝 Join events with guest invitations and responses
- 📊 Reporting system
- 🚫 Conflict detection (overlaps/holidays)

## 🚀 Features
- User System: Signup/login/logout with credential validation

- 4 Job Types:

  - One-time Events (with duration)
  - Periodic Events (daily/weekly/monthly recurrence)
  - Simple Tasks (single timepoint)
  - Join Events (collaborative scheduling with guest invites)

- Smart Scheduling:
  
  - Automatic overlap detection
  - Holiday awareness (via CSV input)
  - Date validation (30-day months, 1404+ Persian calendar support)

- Reporting: Filter jobs by date range/type

## 🌐 Web Interface
UTrello now comes with a responsive web interface for managing your schedule:

- 📅 View and manage events and tasks in-browser
- 🧭 Clean, intuitive UI for job creation and conflict resolution
- 📊 Dashboard and reports accessible by filters
- ⚠️ Real-time feedback on validation or scheduling conflicts

## 📥 Installation

```bash
git clone https://github.com/MahdiAnvarii/UTrello.git
cd UTrello
make
make run
```

Then open your browser and go to:

```bash
http://localhost:5000 
```

## 👨‍💻 Example Usage

- Sign up or log in from the login screen
- Create a task or event by filling in a simple form
- View upcoming events in the dashboard
- Accept or reject join event invitations
- Generate reports by selecting date range/type
