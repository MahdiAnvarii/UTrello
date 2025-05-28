# UTrello - Task & Event Scheduler  
![UTrelloPic](https://drive.google.com/uc?export=view&id=10GTguiuto93vsm8TyHQNkB093Uyds2dG)

## 📝 Repository Description
UTrello is a C++ command-line application that helps users organize tasks, events, and recurring schedules with:
- ✅ User authentication
- 📅 Date/time management
- 🔄 Support for periodic events (daily/weekly/monthly)
- 📊 Reporting system
- 🚫 Conflict detection (overlaps/holidays)

## 🚀 Features
- User System: Signup/login/logout with credential validation

- 3 Job Types:

  - One-time Events (with duration)
  - Periodic Events (daily/weekly/monthly recurrence)
  - Simple Tasks (single timepoint)

- Smart Scheduling:
  
  - Automatic overlap detection
  - Holiday awareness (via CSV input)
  - Date validation (30-day months, 1404+ Persian calendar support)

- Rich CLI:

  - Natural command syntax (e.g., POST event date 1403/05/15 start_time 9 duration 2 title "Meeting")
  - Error handling with clear messages

- Reporting: Filter jobs by date range/type

## 📥 Installation

```bash
git clone https://github.com/MahdiAnvarii/UTrello.git
cd UTrello
make
./UTrello holidays.csv  # Sample holiday file
```

## 💻 Usage Examples

```sh
# User management
POST signup username john password 1234
POST login username john password 1234

# Scheduling
POST event date 1403/06/20 start_time 14 duration 2 title "Team Sync"
POST periodic_event start_date 1403/06/01 end_date 1403/09/01 [...] type Weekly week_days Saturday,Monday

# Reporting
GET report from 1403/05/01 to 1403/06/30 type task
```
