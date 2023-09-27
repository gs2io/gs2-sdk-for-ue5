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

#include "LoginReward/Domain/Model/Namespace.h"
#include "LoginReward/Domain/Model/Namespace.h"
#include "LoginReward/Domain/Model/BonusModelMaster.h"
#include "LoginReward/Domain/Model/CurrentBonusMaster.h"
#include "LoginReward/Domain/Model/BonusModel.h"
#include "LoginReward/Domain/Model/User.h"
#include "LoginReward/Domain/Model/UserAccessToken.h"
#include "LoginReward/Domain/Model/Bonus.h"
#include "LoginReward/Domain/Model/BonusAccessToken.h"
#include "LoginReward/Domain/Model/ReceiveStatus.h"
#include "LoginReward/Domain/Model/ReceiveStatusAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::LoginReward::Domain::Model
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
        Client(MakeShared<Gs2::LoginReward::FGs2LoginRewardRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey("loginReward:Namespace")
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
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FNamespaceDomain>> Result
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
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FNamespace>> Result
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
                const auto ParentKey = FString("loginReward:Namespace");
                const auto Key = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::LoginReward::Model::FNamespace::TypeName,
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
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("loginReward:Namespace");
                const auto Key = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::LoginReward::Model::FNamespace::TypeName,
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
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("loginReward:Namespace");
                const auto Key = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::LoginReward::Model::FNamespace::TypeName, ParentKey, Key);
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

    FNamespaceDomain::FCreateBonusModelMasterTask::FCreateBonusModelMasterTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FCreateBonusModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateBonusModelMasterTask::FCreateBonusModelMasterTask(
        const FCreateBonusModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateBonusModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateBonusModelMaster(
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
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "BonusModelMaster"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FBonusModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::LoginReward::Model::FBonusModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::LoginReward::Domain::Model::FBonusModelMasterDomain>(
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateBonusModelMasterTask>> FNamespaceDomain::CreateBonusModelMaster(
        Request::FCreateBonusModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateBonusModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::LoginReward::Domain::Iterator::FDescribeBonusModelMastersIteratorPtr FNamespaceDomain::BonusModelMasters(
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Iterator::FDescribeBonusModelMastersIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeBonusModelMasters(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::LoginReward::Model::FBonusModelMaster::TypeName,
            Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "BonusModelMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeBonusModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::LoginReward::Model::FBonusModelMaster::TypeName,
            Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "BonusModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusModelMasterDomain> FNamespaceDomain::BonusModelMaster(
        const FString BonusModelName
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FBonusModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            BonusModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(BonusModelName)
        );
    }

    TSharedPtr<Gs2::LoginReward::Domain::Model::FCurrentBonusMasterDomain> FNamespaceDomain::CurrentBonusMaster(
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FCurrentBonusMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::LoginReward::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FUserDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::LoginReward::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FUserAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::LoginReward::Domain::Iterator::FDescribeBonusModelsIteratorPtr FNamespaceDomain::BonusModels(
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Iterator::FDescribeBonusModelsIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeBonusModels(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::LoginReward::Model::FBonusModel::TypeName,
            Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "BonusModel"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeBonusModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::LoginReward::Model::FBonusModel::TypeName,
            Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "BonusModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusModelDomain> FNamespaceDomain::BonusModel(
        const FString BonusModelName
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FBonusModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            BonusModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(BonusModelName)
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
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("loginReward:Namespace");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::LoginReward::Model::FNamespace> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::LoginReward::Model::FNamespace>(
            ParentKey,
            Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
                Self->NamespaceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::LoginReward::Request::FGetNamespaceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                );
                Self->Cache->Put(
                    Gs2::LoginReward::Model::FNamespace::TypeName,
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
            Self->Cache->TryGet<Gs2::LoginReward::Model::FNamespace>(
                ParentKey,
                Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
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
        TFunction<void(Gs2::LoginReward::Model::FNamespacePtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::LoginReward::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::LoginReward::Model::FNamespace>(obj));
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::LoginReward::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
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

