# Bảng Phân Công Nhiệm Vụ Thành Viên 

## 1. Trách nhiệm chuyên môn theo vai trò

| Thành viên | Vai trò phụ trách | Trách nhiệm chính |
| :--- | :--- | :--- |
| **Điền** | Hardware, PCB & Mechanical Engineer | Thiết kế sơ đồ nguyên lý KiCad, layout PCB, gia công và hàn lắp linh kiện phần cứng, thiết kế mô hình 3D CAD và in vỏ hộp (enclosure) cho thiết bị. |
| **Vũ** | Embedded Firmware Engineer | Thiết lập dự án PlatformIO, viết driver đọc cảm biến (GP2Y1010AU0F, BME680, INA219), điều khiển màn hình TFT ST7735, xử lý còi cảnh báo buzzer và đẩy dữ liệu lên Firebase. |
| **Dũng** | Software & Cloud Engineer | Xây dựng giao diện Web Dashboard (HTML5, CSS3, JavaScript, Chart.js), thiết lập và cấu hình cơ sở dữ liệu Google Firebase Realtime Database, tích hợp WebSocket stream dữ liệu thời gian thực. |
| **Cả nhóm** | Testing & Documentation | Khảo sát yêu cầu, thử nghiệm độ ổn định hệ thống, viết báo cáo toàn văn (Chương 1 đến 5), chuẩn bị slide và thuyết trình bảo vệ đồ án. |

---

## 2. Chi tiết phân công công việc theo lộ trình 9 tuần

| Tuần | Công việc chi tiết | Thành viên phụ trách | Trạng thái |
| :---: | :--- | :---: | :---: |
| **Tuần 1** | - Xác định đề tài, khảo sát tiêu chuẩn IAQ (WHO, US-EPA)<br>- Lựa chọn linh kiện phần cứng (ESP32-C3, BME680, GP2Y1010, INA219)<br>- Viết báo cáo Chương 1: Giới thiệu đề tài | Cả nhóm | **Hoàn thành** |
| **Tuần 2** | - Thiết kế kiến trúc hệ thống 3 lớp & khối nguồn pin 2S/BMS<br>- Lập đặc tả kỹ thuật hệ thống<br>- Viết báo cáo Chương 2: Cơ sở lý thuyết & Thiết kế hệ thống | Cả nhóm | **Hoàn thành** |
| **Tuần 3** | - Mua sắm linh kiện BOM, chuẩn bị phôi mạch<br>- Đo kiểm chân cắm ESP32-C3 và cấp nguồn test breadboard | **Điền** (Phần cứng) | **Hoàn thành** |
| **Tuần 4** | - Cắm test giao tiếp I2C cảm biến BME680, INA219 trên breadboard<br>- Ráp mạch đệm RC cho cảm biến bụi, burn-in cảm biến khí<br>- Tạo khung dự án PlatformIO cho ESP32-C3 | **Điền** (Mạch RC/I2C)<br>**Vũ** (Test giao tiếp & Code mẫu) | **Hoàn thành** |
| **Tuần 5** | - Nối dây hoàn chỉnh hệ thống trên breadboard<br>- Viết code đọc sơ bộ cảm biến & test hiển thị màn hình TFT<br>- Thiết kế layout giao diện Web Dashboard (HTML/CSS/JS, Chart.js) | **Điền** (Breadboard toàn hệ thống)<br>**Vũ** (Firmware test màn hình)<br>**Dũng** (Web App UI) | **Hoàn thành** |
| **Tuần 6** *(Hiện tại)* | - Vẽ hoàn thiện sơ đồ nguyên lý trên KiCad (`.kicad_sch`)<br>- Layout đường mạch PCB, xuất file Gerber và chuẩn bị làm board<br>- Lên ý tưởng kích thước sơ bộ vỏ hộp 3D<br>- Hoàn thiện các biểu đồ trực quan hóa dữ liệu trên Web Dashboard | **Điền** (KiCad, PCB Layout & Phác thảo 3D)<br>**Dũng** (Web Charts) | **Đang thực hiện** |
| **Tuần 7** | - Gia công, hàn lắp linh kiện lên mạch PCB hoàn chỉnh<br>- Lập trình firmware đọc chính xác cảm biến bụi, BME680, INA219<br>- Cấu hình dự án Firebase Realtime Database và bảo mật rules | **Điền** (Hàn ráp & đo kiểm PCB)<br>**Vũ** (Firmware cảm biến & TFT)<br>**Dũng** (Cấu hình Firebase RTDB) | **Chờ thực hiện** |
| **Tuần 8** | - Lập trình ESP32-C3 kết nối Wi-Fi và đẩy dữ liệu lên Firebase<br>- Kết nối Web Dashboard với Firebase Web SDK để stream dữ liệu<br>- Lập trình còi buzzer cảnh báo vượt ngưỡng bụi/khí và pin yếu<br>- Thiết kế 3D CAD chi tiết và in 3D vỏ hộp có khe lấy gió | **Vũ** (Wi-Fi, Firebase client, Buzzer)<br>**Dũng** (Web WebSocket kết nối Firebase)<br>**Điền** (Thiết kế 3D, in vỏ hộp & lắp ráp) | **Chờ thực hiện** |
| **Tuần 9** | - Chạy thử nghiệm hệ thống liên tục 24h, đo kiểm dòng tiêu thụ<br>- Hoàn thiện báo cáo toàn văn (Chương 3, 4, 5)<br>- Thiết kế slide thuyết trình, quay video demo và bảo vệ đồ án | Cả nhóm | **Chờ thực hiện** |

---

## 3. Tỷ lệ đóng góp dự kiến

| Thành viên | Tỷ lệ đóng góp | Chữ ký xác nhận |
| :--- | :---: | :---: |
| **Điền** | 33.3% | |
| **Vũ** | 33.3% | |
| **Dũng** | 33.3% | |
