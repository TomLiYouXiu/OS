public class Main {
    public static void main(String[] args) {
        /**
         * step 7: 创建继承类售票窗口
         *          3个窗口
         */
        Thread t1 = new Station("售票窗口1号");
        Thread t2 = new Station("售票窗口2号");
        Thread t3 = new Station("售票窗口3号");
        /**
         * step 8: 三个窗口都处于就绪状态
         */
        t1.start();
        t2.start();
        t3.start();
    }
}

