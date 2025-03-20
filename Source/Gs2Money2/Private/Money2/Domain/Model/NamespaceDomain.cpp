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

#include "Money2/Domain/Model/Namespace.h"
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

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("money2:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetStatus().IsSet())
            {
                Self->Status = Domain->Status = ResultModel->GetStatus();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FNamespace>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateStoreContentModelMasterTask::FCreateStoreContentModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateStoreContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateStoreContentModelMasterTask::FCreateStoreContentModelMasterTask(
        const FCreateStoreContentModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateStoreContentModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateStoreContentModelMasterTask>> FNamespaceDomain::CreateStoreContentModelMaster(
        Request::FCreateStoreContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStoreContentModelMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateStoreSubscriptionContentModelMasterTask::FCreateStoreSubscriptionContentModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateStoreSubscriptionContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateStoreSubscriptionContentModelMasterTask::FCreateStoreSubscriptionContentModelMasterTask(
        const FCreateStoreSubscriptionContentModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateStoreSubscriptionContentModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateStoreSubscriptionContentModelMasterTask>> FNamespaceDomain::CreateStoreSubscriptionContentModelMaster(
        Request::FCreateStoreSubscriptionContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStoreSubscriptionContentModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesByCurrencyIteratorPtr FNamespaceDomain::DailyTransactionHistoriesByCurrency(
        const FString Currency,
        const int32 Year,
        const TOptional<int32> Month
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesByCurrencyIterator>(
            Gs2,
            Client,
            NamespaceName,
            Currency,
            Year,
            Month
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDailyTransactionHistoriesByCurrency(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "DailyTransactionHistory"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeDailyTransactionHistoriesByCurrency(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "DailyTransactionHistory"
            ),
            CallbackID
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesIteratorPtr FNamespaceDomain::DailyTransactionHistories(
        const int32 Year,
        const TOptional<int32> Month,
        const TOptional<int32> Day
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesIterator>(
            Gs2,
            Client,
            NamespaceName,
            Year,
            Month,
            Day
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDailyTransactionHistories(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "DailyTransactionHistory"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeDailyTransactionHistories(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "DailyTransactionHistory"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain> FNamespaceDomain::DailyTransactionHistory(
        const int32 Year,
        const int32 Month,
        const int32 Day,
        const FString Currency
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain>(
            Gs2,
            Service,
            NamespaceName,
            Year,
            Month,
            Day,
            Currency == TEXT("") ? TOptional<FString>() : TOptional<FString>(Currency)
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain> FNamespaceDomain::CurrentModelMaster(
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelsIteratorPtr FNamespaceDomain::StoreContentModels(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreContentModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FStoreContentModel::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StoreContentModel"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeStoreContentModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FStoreContentModel::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StoreContentModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelDomain> FNamespaceDomain::StoreContentModel(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FStoreContentModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeUnusedBalancesIteratorPtr FNamespaceDomain::UnusedBalances(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeUnusedBalancesIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeUnusedBalances(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FUnusedBalance::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "UnusedBalance"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeUnusedBalances(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FUnusedBalance::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "UnusedBalance"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FUnusedBalanceDomain> FNamespaceDomain::UnusedBalance(
        const FString Currency
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FUnusedBalanceDomain>(
            Gs2,
            Service,
            NamespaceName,
            Currency == TEXT("") ? TOptional<FString>() : TOptional<FString>(Currency)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelMastersIteratorPtr FNamespaceDomain::StoreContentModelMasters(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreContentModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StoreContentModelMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeStoreContentModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StoreContentModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain> FNamespaceDomain::StoreContentModelMaster(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelsIteratorPtr FNamespaceDomain::StoreSubscriptionContentModels(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreSubscriptionContentModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModel::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StoreSubscriptionContentModel"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeStoreSubscriptionContentModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModel::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StoreSubscriptionContentModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelDomain> FNamespaceDomain::StoreSubscriptionContentModel(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelMastersIteratorPtr FNamespaceDomain::StoreSubscriptionContentModelMasters(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreSubscriptionContentModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StoreSubscriptionContentModelMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeStoreSubscriptionContentModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StoreSubscriptionContentModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain> FNamespaceDomain::StoreSubscriptionContentModelMaster(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
        );
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("money2:Namespace");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money2::Model::FNamespace> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FNamespace>(
            ParentKey,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheKey(
                Self->NamespaceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Money2::Request::FGetNamespaceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "namespace")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FNamespace>(
                ParentKey,
                Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FNamespacePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FNamespace>(obj));
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
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

