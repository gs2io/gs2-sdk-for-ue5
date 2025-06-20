/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Money2/Domain/Model/DailyTransactionHistory.h"
#include "Money2/Domain/Model/Namespace.h"
#include "Money2/Domain/Model/User.h"
#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Domain/Model/Wallet.h"
#include "Money2/Domain/Model/WalletAccessToken.h"
#include "Money2/Domain/Model/Event.h"
#include "Money2/Domain/Model/EventAccessToken.h"
#include "Money2/Domain/Model/SubscriptionStatus.h"
#include "Money2/Domain/Model/SubscriptionStatusAccessToken.h"
#include "Money2/Domain/Model/RefundHistory.h"
#include "Money2/Domain/Model/StoreContentModel.h"
#include "Money2/Domain/Model/StoreContentModelMaster.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModel.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModelMaster.h"
#include "Money2/Domain/Model/CurrentModelMaster.h"
#include "Money2/Domain/Model/DailyTransactionHistory.h"
#include "Money2/Domain/Model/UnusedBalance.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FDailyTransactionHistoryDomain::FDailyTransactionHistoryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<int32> Year,
        const TOptional<int32> Month,
        const TOptional<int32> Day,
        const TOptional<FString> Currency
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Year(Year),
        Month(Month),
        Day(Day),
        Currency(Currency),
        ParentKey(Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "DailyTransactionHistory"
        ))
    {
    }

    FDailyTransactionHistoryDomain::FDailyTransactionHistoryDomain(
        const FDailyTransactionHistoryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Year(From.Year),
        Month(From.Month),
        Day(From.Day),
        Currency(From.Currency),
        ParentKey(From.ParentKey)
    {

    }

    FDailyTransactionHistoryDomain::FGetTask::FGetTask(
        const TSharedPtr<FDailyTransactionHistoryDomain>& Self,
        const Request::FGetDailyTransactionHistoryRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDailyTransactionHistoryDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDailyTransactionHistoryDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithYear(Self->Year)
            ->WithMonth(Self->Month)
            ->WithDay(Self->Day)
            ->WithCurrency(Self->Currency);
        const auto Future = Self->Client->GetDailyTransactionHistory(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDailyTransactionHistoryDomain::FGetTask>> FDailyTransactionHistoryDomain::Get(
        Request::FGetDailyTransactionHistoryRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FDailyTransactionHistoryDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<int32> Year,
        TOptional<int32> Month,
        TOptional<int32> Day,
        TOptional<FString> Currency,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Year.IsSet() ? FString::FromInt(*Year) : "null") + ":" +
            (Month.IsSet() ? FString::FromInt(*Month) : "null") + ":" +
            (Day.IsSet() ? FString::FromInt(*Day) : "null") + ":" +
            (Currency.IsSet() ? *Currency : "null") + ":" +
            ChildType;
    }

    FString FDailyTransactionHistoryDomain::CreateCacheKey(
        TOptional<int32> Year,
        TOptional<int32> Month,
        TOptional<int32> Day,
        TOptional<FString> Currency
    )
    {
        return FString("") +
            (Year.IsSet() ? FString::FromInt(*Year) : "null") + ":" + 
            (Month.IsSet() ? FString::FromInt(*Month) : "null") + ":" + 
            (Day.IsSet() ? FString::FromInt(*Day) : "null") + ":" + 
            (Currency.IsSet() ? *Currency : "null");
    }

    FDailyTransactionHistoryDomain::FModelTask::FModelTask(
        const TSharedPtr<FDailyTransactionHistoryDomain> Self
    ): Self(Self)
    {

    }

    FDailyTransactionHistoryDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDailyTransactionHistoryDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FDailyTransactionHistory>(
            Self->ParentKey,
            Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain::CreateCacheKey(
                Self->Year,
                Self->Month,
                Self->Day,
                Self->Currency
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Money2::Request::FGetDailyTransactionHistoryRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain::CreateCacheKey(
                    Self->Year,
                    Self->Month,
                    Self->Day,
                    Self->Currency
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "dailyTransactionHistory")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FDailyTransactionHistory>(
                Self->ParentKey,
                Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain::CreateCacheKey(
                    Self->Year,
                    Self->Month,
                    Self->Day,
                    Self->Currency
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDailyTransactionHistoryDomain::FModelTask>> FDailyTransactionHistoryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDailyTransactionHistoryDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDailyTransactionHistoryDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FDailyTransactionHistoryPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain::CreateCacheKey(
                Year,
                Month,
                Day,
                Currency
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>(obj));
            }
        );
    }

    void FDailyTransactionHistoryDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain::CreateCacheKey(
                Year,
                Month,
                Day,
                Currency
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

