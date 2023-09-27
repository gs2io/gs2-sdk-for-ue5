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

#include "Enchant/Domain/Model/Namespace.h"
#include "Enchant/Domain/Model/Namespace.h"
#include "Enchant/Domain/Model/BalanceParameterModel.h"
#include "Enchant/Domain/Model/BalanceParameterModelMaster.h"
#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Domain/Model/RarityParameterModelMaster.h"
#include "Enchant/Domain/Model/CurrentParameterMaster.h"
#include "Enchant/Domain/Model/User.h"
#include "Enchant/Domain/Model/UserAccessToken.h"
#include "Enchant/Domain/Model/BalanceParameterStatus.h"
#include "Enchant/Domain/Model/BalanceParameterStatusAccessToken.h"
#include "Enchant/Domain/Model/RarityParameterStatus.h"
#include "Enchant/Domain/Model/RarityParameterStatusAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Enchant::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Enchant::FGs2EnchantRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey("enchant:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespaceStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        Domain->Status = Domain->Status = ResultModel->GetStatus();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FNamespace>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("enchant:Namespace");
                const auto Key = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Enchant::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("enchant:Namespace");
                const auto Key = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Enchant::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
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
        const TSharedPtr<FNamespaceDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("enchant:Namespace");
                const auto Key = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Enchant::Model::FNamespace::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateBalanceParameterModelMasterTask::FCreateBalanceParameterModelMasterTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FCreateBalanceParameterModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateBalanceParameterModelMasterTask::FCreateBalanceParameterModelMasterTask(
        const FCreateBalanceParameterModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateBalanceParameterModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateBalanceParameterModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "BalanceParameterModelMaster"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Enchant::Model::FBalanceParameterModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateBalanceParameterModelMasterTask>> FNamespaceDomain::CreateBalanceParameterModelMaster(
        Request::FCreateBalanceParameterModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateBalanceParameterModelMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateRarityParameterModelMasterTask::FCreateRarityParameterModelMasterTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FCreateRarityParameterModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateRarityParameterModelMasterTask::FCreateRarityParameterModelMasterTask(
        const FCreateRarityParameterModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateRarityParameterModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateRarityParameterModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RarityParameterModelMaster"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateRarityParameterModelMasterTask>> FNamespaceDomain::CreateRarityParameterModelMaster(
        Request::FCreateRarityParameterModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateRarityParameterModelMasterTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FCurrentParameterMasterDomain> FNamespaceDomain::CurrentParameterMaster(
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FCurrentParameterMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName
        );
    }

    Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterModelsIteratorPtr FNamespaceDomain::BalanceParameterModels(
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterModelsIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeBalanceParameterModels(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Enchant::Model::FBalanceParameterModel::TypeName,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "BalanceParameterModel"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeBalanceParameterModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Enchant::Model::FBalanceParameterModel::TypeName,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "BalanceParameterModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterModelDomain> FNamespaceDomain::BalanceParameterModel(
        const FString ParameterName
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FBalanceParameterModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            ParameterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ParameterName)
        );
    }

    Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterModelMastersIteratorPtr FNamespaceDomain::BalanceParameterModelMasters(
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterModelMastersIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeBalanceParameterModelMasters(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Enchant::Model::FBalanceParameterModelMaster::TypeName,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "BalanceParameterModelMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeBalanceParameterModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Enchant::Model::FBalanceParameterModelMaster::TypeName,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "BalanceParameterModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain> FNamespaceDomain::BalanceParameterModelMaster(
        const FString ParameterName
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            ParameterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ParameterName)
        );
    }

    Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterModelsIteratorPtr FNamespaceDomain::RarityParameterModels(
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterModelsIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRarityParameterModels(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Enchant::Model::FRarityParameterModel::TypeName,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RarityParameterModel"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeRarityParameterModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Enchant::Model::FRarityParameterModel::TypeName,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RarityParameterModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterModelDomain> FNamespaceDomain::RarityParameterModel(
        const FString ParameterName
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FRarityParameterModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            ParameterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ParameterName)
        );
    }

    Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterModelMastersIteratorPtr FNamespaceDomain::RarityParameterModelMasters(
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterModelMastersIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRarityParameterModelMasters(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RarityParameterModelMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeRarityParameterModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RarityParameterModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain> FNamespaceDomain::RarityParameterModelMaster(
        const FString ParameterName
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            ParameterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ParameterName)
        );
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FUserDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FUserAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken
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
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("enchant:Namespace");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Enchant::Model::FNamespace> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Enchant::Model::FNamespace>(
            ParentKey,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheKey(
                Self->NamespaceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Enchant::Request::FGetNamespaceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                );
                Self->Cache->Put(
                    Gs2::Enchant::Model::FNamespace::TypeName,
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
            Self->Cache->TryGet<Gs2::Enchant::Model::FNamespace>(
                ParentKey,
                Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheKey(
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
        TFunction<void(Gs2::Enchant::Model::FNamespacePtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Enchant::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Enchant::Model::FNamespace>(obj));
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Enchant::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheKey(
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

