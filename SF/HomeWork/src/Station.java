// 3个站台同时出售火车票，火车票共有20张
/**
 * 注明：
 * 静态变量生命周期是类的生命周期；
 *
 * step 1: 创建一个站台类继承java.lang.Thread
 */
public class Station extends Thread {
    /**
     * step 2: 创建有参构造方法，给线程名称赋值
     * @param name
     */
    public Station(String name) {
        super(name);
    }
    /**
     * step 3：创建静态变量，类的变量
     */
    static int tick = 20;
    /**
     * step 4: 创建静态钥匙，类的变量
     *
     * 关键思想：通过[静态，没有static关键字可正常运行]变量的占用判断是否对另一个静态变量操作
     */
     Object lock = "one";

    /**
     * step 5: 重写run()方法，实现买票操作
     */
    @Override
    public void run() {
        while(tick > 0) {
            /**
             * step 6: 每个线程使用同一静态变量，一个线程占用该静态变量时，其他线程不允许进入
             *          该线程出来这个代码块后，不使用该静态变量
             *
             * 关键思想：synchronized与静态变量lock配合，操作系统保证cpu只运行三个线程中唯一一个线程中此段代码，
             *           其他线程不能被执行。唯一一个线程的此段代码运行结束后，cpu可同步执行3个线程线程。
             */
            synchronized (lock) {
                if(tick > 0) {
                    System.out.println(getName()+"卖出了第"+tick+"张票");
                    tick--;
                }else {
                    System.out.println("票卖完了");
                }
            }
            try {
                sleep(500);
            } catch(Exception e) {
                e.printStackTrace();
            }
        }
    }
}


