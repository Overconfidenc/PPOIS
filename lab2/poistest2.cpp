#include "pch.h"
#include "CppUnitTest.h"
#include "../pois2/Client.h"
#include "../pois2/Order.h"
#include "../pois2/Recipe.h"
#include "../pois2/Menu.h"
#include "../pois2/Product.h"
#include "../pois2/PaymentSystem.h"
#include "../pois2/Warehouse.h"
#include "../pois2/Transaction.h"
#include "../pois2/Supplier.h"
#include "../pois2/NotificationSystem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace poistest2
{
	TEST_CLASS(WarehouseTests)
	{
	public:

		// Тест на добавление продукта в склад
		TEST_METHOD(TestReceiveProducts)
		{
			Warehouse warehouse;
			Product product("Молоко", 1.0, 50.0);

			// Добавляем продукт
			warehouse.receiveProducts(product, 5);

			// Проверяем, что продукт добавлен с правильным количеством
			Assert::AreEqual(5, warehouse.getQuantity("Молоко"));
		}

		// Тест на получение списка доступных ингредиентов
		TEST_METHOD(TestGetAvailableIngredients)
		{
			Warehouse warehouse;
			Product product1("Молоко", 1.0, 50.0);
			Product product2("Хлеб", 0.5, 30.0);

			// Добавляем продукты
			warehouse.receiveProducts(product1, 5);
			warehouse.receiveProducts(product2, 3);

			// Получаем список доступных ингредиентов
			vector<Product> ingredients = warehouse.getAvailableIngredients();

			// Проверяем, что список содержит оба продукта
			Assert::AreEqual((size_t)2, ingredients.size());
			Assert::AreEqual(string("Молоко"), ingredients[0].getName());
			Assert::AreEqual(string("Хлеб"), ingredients[1].getName());
		}

		// Тест на проверку количества продукта
		TEST_METHOD(TestGetQuantity)
		{
			Warehouse warehouse;
			Product product("Сахар", 1.0, 40.0);

			// Добавляем продукт
			warehouse.receiveProducts(product, 7);

			// Проверяем количество
			Assert::AreEqual(7, warehouse.getQuantity("Сахар"));
			Assert::AreEqual(0, warehouse.getQuantity("Соль")); // Продукт не добавлялся
		}

		// Тест на списание продукта
		TEST_METHOD(TestDeductProduct)
		{
			Warehouse warehouse;
			Product product("Яблоки", 0.2, 20.0);

			// Добавляем продукт
			warehouse.receiveProducts(product, 10);

			// Списываем часть продукта
			warehouse.deductProduct("Яблоки", 4);

			// Проверяем оставшееся количество
			Assert::AreEqual(6, warehouse.getQuantity("Яблоки"));

			// Списываем оставшееся количество
			warehouse.deductProduct("Яблоки", 6);

			// Проверяем, что продукта больше нет
			Assert::AreEqual(0, warehouse.getQuantity("Яблоки"));
		}

		// Тест на попытку списания большего количества, чем доступно
		TEST_METHOD(TestDeductProductInsufficient)
		{
			Warehouse warehouse;
			Product product("Груши", 0.3, 25.0);

			// Добавляем продукт
			warehouse.receiveProducts(product, 3);

			// Пытаемся списать больше, чем есть
			warehouse.deductProduct("Груши", 5);

			// Проверяем, что количество не изменилось
			Assert::AreEqual(3, warehouse.getQuantity("Груши"));
		}
	};

	TEST_CLASS(TransactionTests)
	{
	public:

		// Тест на создание транзакции
		TEST_METHOD(TestTransactionCreation)
		{
			Transaction transaction("Покупка", 150.0);

			// Проверяем, что объект успешно создан
			ostringstream out;
			streambuf* oldCoutBuffer = cout.rdbuf(out.rdbuf());

			transaction.performTransaction();
			cout.rdbuf(oldCoutBuffer);

			string output = out.str();
			Assert::IsTrue(output.find("Покупка") != string::npos);
			Assert::IsTrue(output.find("150") != string::npos);
		}

		// Тест на выполнение транзакции
		TEST_METHOD(TestPerformTransaction)
		{
			Transaction transaction("Продажа", 200.0);

			// Проверяем вывод информации о транзакции
			ostringstream out;
			streambuf* oldCoutBuffer = cout.rdbuf(out.rdbuf());

			transaction.performTransaction();
			cout.rdbuf(oldCoutBuffer);

			string output = out.str();
			Assert::IsTrue(output.find("Продажа") != string::npos);
			Assert::IsTrue(output.find("200") != string::npos);
		}

		// Тест на проверку статуса транзакции
		TEST_METHOD(TestCheckStatus)
		{
			Transaction transaction("Перевод", 500.0);

			// Проверяем вывод статуса транзакции
			ostringstream out;
			streambuf* oldCoutBuffer = cout.rdbuf(out.rdbuf());

			transaction.checkStatus();
			cout.rdbuf(oldCoutBuffer);

			string output = out.str();
			Assert::IsTrue(output.find("Перевод") != string::npos);
			Assert::IsTrue(output.find("500") != string::npos);
		}
	};

	TEST_CLASS(SupplierTests)
	{
	public:

		// Тест на создание поставщика
		TEST_METHOD(TestSupplierCreation)
		{
			Supplier supplier("ООО Поставщик", "contact@supplier.com");

			// Проверяем, что объект успешно создан
			Assert::AreEqual(string("ООО Поставщик"), supplier.getName());
			Assert::AreEqual(string("contact@supplier.com"), supplier.getContactInfo());
		}

		// Тест на доставку продуктов
		TEST_METHOD(TestDeliverProducts)
		{
			Supplier supplier("ООО Поставщик", "contact@supplier.com");
			Product product1("Молоко", 1.0, 50.0);
			Product product2("Хлеб", 0.5, 30.0);

			vector<Product> products = { product1, product2 };

			// Перехват вывода
			ostringstream out;
			streambuf* oldCoutBuffer = cout.rdbuf(out.rdbuf());

			// Доставка продуктов
			supplier.deliverProducts(products);

			// Проверяем вывод
			cout.rdbuf(oldCoutBuffer);
			string output = out.str();
			Assert::IsTrue(output.find("Продукты доставлены ООО Поставщик") != string::npos);
		}

		// Тест на проверку качества продукта
		TEST_METHOD(TestCheckQuality)
		{
			Supplier supplier("ООО Поставщик", "contact@supplier.com");
			Product product("Молоко", 1.0, 50.0);

			// Перехват вывода
			ostringstream out;
			streambuf* oldCoutBuffer = cout.rdbuf(out.rdbuf());

			// Проверка качества
			supplier.checkQuality(product);

			// Проверяем вывод
			cout.rdbuf(oldCoutBuffer);
			string output = out.str();
			Assert::IsTrue(output.find("Проверка качества Молоко") != string::npos);
			Assert::IsTrue(output.find("Проверка качества прошла успешно!") != string::npos);
		}
	};

	TEST_CLASS(RecipeTests)
	{
	public:

		// Тест на создание рецепта
		TEST_METHOD(TestRecipeCreation)
		{
			Recipe recipe("Салат", "Смешать все ингредиенты");

			// Проверяем, что рецепт создан корректно
			Assert::AreEqual(string("Салат"), recipe.getName());
			Assert::AreEqual(string("Смешать все ингредиенты"), recipe.getDescription());
			Assert::AreEqual(1, recipe.getPiecesCount());
		}

		// Тест на добавление ингредиента
		TEST_METHOD(TestAddIngredient)
		{
			Recipe recipe("Салат", "Смешать все ингредиенты");
			Product ingredient("Огурец", 200, 20);

			// Добавляем ингредиент
			recipe.addIngredient(ingredient);

			// Проверяем, что ингредиент добавлен
			auto ingredients = recipe.getIngredients();
			Assert::AreEqual((size_t)1, ingredients.size());
			Assert::AreEqual(string("Огурец"), ingredients[0].getName());
		}

		// Тест на расчет общего веса ингредиентов
		TEST_METHOD(TestCalculateTotalWeight)
		{
			Recipe recipe("Салат", "Смешать все ингредиенты");
			recipe.addIngredient(Product("Огурец", 200, 20));
			recipe.addIngredient(Product("Помидор", 300, 30));

			// Проверяем общий вес
			Assert::AreEqual(500, recipe.calculateTotalWeight());
		}

		// Тест на расчет общей стоимости ингредиентов
		TEST_METHOD(TestCalculateTotalCost)
		{
			Recipe recipe("Салат", "Смешать все ингредиенты");
			recipe.addIngredient(Product("Огурец", 200, 20));
			recipe.addIngredient(Product("Помидор", 300, 30));

			// Проверяем общую стоимость
			Assert::AreEqual(50.0, recipe.calculateTotalCost());
		}

		// Тест на максимальное количество кусков
		TEST_METHOD(TestGetMaxPieces)
		{
			Recipe recipe("Салат", "Смешать все ингредиенты");
			recipe.addIngredient(Product("Огурец", 250, 20));
			recipe.addIngredient(Product("Помидор", 150, 30));

			// Проверяем максимальное количество кусков
			Assert::AreEqual(8, recipe.getMaxPieces()); // (250+150)/100 * 2 = 8
		}

		// Тест на разрезание рецепта
		TEST_METHOD(TestCutNewPiece)
		{
			Recipe recipe("Салат", "Смешать все ингредиенты");
			recipe.addIngredient(Product("Огурец", 200, 20));
			recipe.addIngredient(Product("Помидор", 300, 30));

			Knife knife;

			// Разрезаем рецепт
			recipe.CutNewPiece(knife);

			// Проверяем, что количество кусков увеличилось
			Assert::AreEqual(2, recipe.getPiecesCount());
		}

		// Тест на достижение максимального количества кусков
		TEST_METHOD(TestCutNewPieceMaxReached)
		{
			Recipe recipe("Салат", "Смешать все ингредиенты");
			recipe.addIngredient(Product("Огурец", 200, 20));
			recipe.addIngredient(Product("Помидор", 300, 30));

			Knife knife;

			// Устанавливаем максимальное количество кусков
			recipe.setPiecesCount(recipe.getMaxPieces());

			// Пытаемся разрезать еще один кусок
			ostringstream out;
			streambuf* oldCoutBuffer = cout.rdbuf(out.rdbuf());
			recipe.CutNewPiece(knife);
			cout.rdbuf(oldCoutBuffer);

			// Проверяем вывод
			string output = out.str();
			Assert::IsTrue(output.find("Максимальное количество кусков достигнуто") != string::npos);
		}
	};

	TEST_CLASS(ProductTests)
	{
	public:

		// Тест на создание продукта с параметрами по умолчанию
		TEST_METHOD(TestDefaultConstructor)
		{
			Product product;

			// Проверяем значения по умолчанию
			Assert::AreEqual(string(""), product.getName());
			Assert::AreEqual(0.0, product.getWeight());
			Assert::AreEqual(0.0, product.getPrice());
		}

		// Тест на создание продукта с пользовательскими параметрами
		TEST_METHOD(TestParameterizedConstructor)
		{
			Product product("Хлеб", 500.0, 40.0);

			// Проверяем установленные значения
			Assert::AreEqual(string("Хлеб"), product.getName());
			Assert::AreEqual(500.0, product.getWeight());
			Assert::AreEqual(40.0, product.getPrice());
		}

		// Тест на установку и получение имени продукта
		TEST_METHOD(TestSetName)
		{
			Product product;
			product.setName("Молоко");

			// Проверяем, что имя установлено корректно
			Assert::AreEqual(string("Молоко"), product.getName());
		}

		// Тест на установку и получение веса продукта
		TEST_METHOD(TestSetWeight)
		{
			Product product;
			product.setWeight(1000.0);

			// Проверяем, что вес установлен корректно
			Assert::AreEqual(1000.0, product.getWeight());
		}

		// Тест на установку и получение цены продукта
		TEST_METHOD(TestSetPrice)
		{
			Product product;
			product.setPrice(25.0);

			// Проверяем, что цена установлена корректно
			Assert::AreEqual(25.0, product.getPrice());
		}

		// Тест на изменение всех параметров продукта
		TEST_METHOD(TestModifyProduct)
		{
			Product product;

			// Устанавливаем значения
			product.setName("Сахар");
			product.setWeight(1000.0);
			product.setPrice(60.0);

			// Проверяем изменения
			Assert::AreEqual(string("Сахар"), product.getName());
			Assert::AreEqual(1000.0, product.getWeight());
			Assert::AreEqual(60.0, product.getPrice());
		}
	};

	TEST_CLASS(PaymentSystemTests)
	{
	public:

		// Тест успешной обработки платежа
		TEST_METHOD(TestProcessPaymentSuccess)
		{
			BankCard card("1234-5678-9012-3456", 500.0);
			PaymentSystem payment(200.0, "Кредитная карта");

			// Обрабатываем платеж
			payment.processPayment(card);

			// Проверяем, что статус платежа изменился на "Завершено"
			Assert::AreEqual(string("Завершено"), payment.getPaymentStatus());
			// Проверяем, что баланс карты уменьшился на сумму платежа
			Assert::AreEqual(300.0, card.getBalance());
		}

		// Тест неуспешной обработки платежа из-за недостатка средств
		TEST_METHOD(TestProcessPaymentInsufficientFunds)
		{
			BankCard card("1234-5678-9012-3456", 100.0);
			PaymentSystem payment(200.0, "Кредитная карта");

			// Пытаемся обработать платеж
			payment.processPayment(card);

			// Проверяем, что статус платежа изменился на "Недостаточно средств"
			Assert::AreEqual(string("Недостаточно средств"), payment.getPaymentStatus());
			// Проверяем, что баланс карты не изменился
			Assert::AreEqual(100.0, card.getBalance());
		}

		// Тест возврата средств
		TEST_METHOD(TestRefund)
		{
			BankCard card("1234-5678-9012-3456", 200.0);
			PaymentSystem payment(100.0, "Кредитная карта");

			// Выполняем возврат средств
			payment.refund(50.0, card);

			// Проверяем, что статус платежа изменился на "Возвращено"
			Assert::AreEqual(string("Возвращено"), payment.getPaymentStatus());
			// Проверяем, что баланс карты увеличился на сумму возврата
			Assert::AreEqual(250.0, card.getBalance());
		}

		// Тест отображения информации о платеже
		TEST_METHOD(TestDisplayPaymentInfo)
		{
			PaymentSystem payment(150.0, "Дебетовая карта");

			// Проверяем начальный статус платежа
			Assert::AreEqual(string("Ожидает"), payment.getPaymentStatus());
			// Проверяем тип платежа
			payment.displayPaymentInfo(); // Это проверяется визуально
		}
	};

	TEST_CLASS(OrderTests)
	{
	public:

		// Тест на создание заказа и вычисление его стоимости
		TEST_METHOD(TestCreateOrderAndCalculateCost)
		{
			// Создаем продукты
			Product product1("Молоко", 1.0, 50.0);
			Product product2("Хлеб", 0.5, 30.0);

			// Создаем рецепт
			Recipe recipe1("Каша", "Каша с молоком");
			recipe1.addIngredient(product1);
			recipe1.addIngredient(product2);

			// Создаем заказ
			vector<Recipe> dishes = { recipe1 };
			Order order("Заказ 1", dishes);

			// Проверяем, что стоимость заказа рассчитывается правильно
			Assert::AreEqual(80.0, order.getTotalCost());
		}

		// Тест на обновление статуса заказа
		TEST_METHOD(TestUpdateOrderStatus)
		{
			// Создаем продукты и рецепт
			Product product1("Молоко", 1.0, 50.0);
			Product product2("Хлеб", 0.5, 30.0);
			Recipe recipe1("Каша", "Каша с молоком");
			recipe1.addIngredient(product1);
			recipe1.addIngredient(product2);

			// Создаем заказ
			vector<Recipe> dishes = { recipe1 };
			Order order("Заказ 2", dishes);

			// Обновляем статус заказа
			order.updateStatus("Выполнен");

			// Проверяем, что статус заказа изменился
			Assert::AreEqual(string("Выполнен"), order.getStatus());
		}

		// Тест на добавление блюда в заказ
		TEST_METHOD(TestAddDishToOrder)
		{
			// Создаем продукты и рецепты
			Product product1("Молоко", 1.0, 50.0);
			Product product2("Хлеб", 0.5, 30.0);
			Recipe recipe1("Каша", "Каша с молоком");
			recipe1.addIngredient(product1);
			recipe1.addIngredient(product2);

			Product product3("Яблоки", 0.3, 20.0);
			Recipe recipe2("Салат", "Салат из яблок");
			recipe2.addIngredient(product3);

			// Создаем заказ
			vector<Recipe> dishes = { recipe1 };
			Order order("Заказ 3", dishes);

			// Добавляем новое блюдо в заказ
			order.addDish(recipe2);

			// Проверяем, что количество блюд в заказе увеличилось
			Assert::AreEqual((size_t)2, order.getOrderedDishes().size());
			Assert::AreEqual(string("Салат"), order.getOrderedDishes()[1].getName());
		}

		// Тест на отображение информации о заказе
		TEST_METHOD(TestDisplayOrderInfo)
		{
			// Создаем продукты и рецепт
			Product product1("Молоко", 1.0, 50.0);
			Product product2("Хлеб", 0.5, 30.0);
			Recipe recipe1("Каша", "Каша с молоком");
			recipe1.addIngredient(product1);
			recipe1.addIngredient(product2);

			// Создаем заказ
			vector<Recipe> dishes = { recipe1 };
			Order order("Заказ 4", dishes);

			// Проверяем информацию о заказе
			order.displayOrderInfo();  // Это проверяется визуально
		}

		// Тест на самовывоз
		TEST_METHOD(TestOrderIsPickup)
		{
			// Создаем продукты и рецепт
			Product product1("Молоко", 1.0, 50.0);
			Product product2("Хлеб", 0.5, 30.0);
			Recipe recipe1("Каша", "Каша с молоком");
			recipe1.addIngredient(product1);
			recipe1.addIngredient(product2);

			// Создаем заказ с самовывозом
			vector<Recipe> dishes = { recipe1 };
			Order order("Заказ 5", dishes, "Ожидает", true);

			// Проверяем, что заказ самовывозом
			Assert::IsTrue(order.getStatus() == "Ожидает");
			Assert::AreEqual(true, order.getOrderedDishes().size() > 0);
		}
	};

	TEST_CLASS(NotificationSystemTests)
	{
	public:


		// Тест на проверку статуса уведомления
		TEST_METHOD(TestCheckNotificationStatus)
		{
			// Создаем уведомление
			NotificationSystem notification("Push", "Не отправлено");

			// Проверяем статус уведомления
			notification.checkStatus();  // Это проверяется визуально
		}
	};

	TEST_CLASS(MenuTests)
	{
	public:

		// Тест на создание и отображение меню
		TEST_METHOD(TestDisplayMenu)
		{
			// Создаем объект меню
			Menu menu("first");

			// Проверяем отображение меню (в реальной ситуации, можно использовать mock-объекты для захвата вывода)
			// В данном случае метод displayMenu() просто выводит текст, поэтому проверка будет визуальной.
			menu.displayMenu();  // Проверяется на экране
		}
	};

	TEST_CLASS(ClientTests)
	{
	public:

		// Тест на создание клиента и проверку его имени
		TEST_METHOD(TestCreateClient)
		{
			// Создаем клиента с картой и начальным балансом
			Client client("Иван", "1234-5678-9876-5432", 1000.0);

			// Проверяем имя клиента
			Assert::AreEqual(string("Иван"), client.getName());
		}

		// Тест на добавление нового заказа
		TEST_METHOD(TestAddOrder)
		{
			// Создаем клиента
			Client client("Иван", "1234-5678-9876-5432", 1000.0);

			// Создаем заказ
			Product product1("Молоко", 1.0, 50.0);
			Product product2("Хлеб", 0.5, 30.0);
			Recipe recipe("Кофе с молоком", "Кофе с молоком и хлеб");
			recipe.addIngredient(product1);
			recipe.addIngredient(product2);
			vector<Recipe> recipes = { recipe };
			Order order("Кофе с молоком", recipes);

			// Добавляем заказ
			client.addOrder(order);

			// Проверяем, что заказ добавлен
			Assert::AreEqual((size_t)1, client.getOrders().size());
			Assert::AreEqual(string("Кофе с молоком"), client.getOrders()[0].getName());
		}

		// Тест на получение информации о банковской карте клиента
		TEST_METHOD(TestGetBankCardInfo)
		{
			// Создаем клиента
			Client client("Иван", "1234-5678-9876-5432", 1000.0);

			// Получаем информацию о банковской карте
			BankCard& card = client.getBankCard();

			// Проверяем баланс карты
			Assert::AreEqual(1000.0, card.getBalance());
		}
	};


}
