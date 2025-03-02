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

#include "Money2/Domain/Model/StoreSubscriptionContentModelMaster.h"
#include "Money2/Domain/Model/Namespace.h"
#include "Money2/Domain/Model/User.h"
#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Domain/Model/Wallet.h"
#include "Money2/Domain/Model/WalletAccessToken.h"
#include "Money2/Domain/Model/Event.h"
#include "Money2/Domain/Model/EventAccessToken.h"
#include "Money2/Domain/Model/SubscriptionStatus.h"
#include "Money2/Domain/Model/SubscriptionStatusAccessToken.h"
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

    FStoreSubscriptionContentModelMasterDomain::FStoreSubscriptionContentModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ContentName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ContentName(ContentName),
        ParentKey(Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "StoreSubscriptionContentModelMaster"
        ))
    {
    }

    FStoreSubscriptionContentModelMasterDomain::FStoreSubscriptionContentModelMasterDomain(
        const FStoreSubscriptionContentModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ContentName(From.ContentName),
        ParentKey(From.ParentKey)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FStoreSubscriptionContentModelMasterDomain>& Self,
        const Request::FGetStoreSubscriptionContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreSubscriptionContentModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithContentName(Self->ContentName);
        const auto Future = Self->Client->GetStoreSubscriptionContentModelMaster(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "StoreSubscriptionContentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FGetTask>> FStoreSubscriptionContentModelMasterDomain::Get(
        Request::FGetStoreSubscriptionContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStoreSubscriptionContentModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FStoreSubscriptionContentModelMasterDomain>& Self,
        const Request::FUpdateStoreSubscriptionContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreSubscriptionContentModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithContentName(Self->ContentName);
        const auto Future = Self->Client->UpdateStoreSubscriptionContentModelMaster(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "StoreSubscriptionContentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FUpdateTask>> FStoreSubscriptionContentModelMasterDomain::Update(
        Request::FUpdateStoreSubscriptionContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FStoreSubscriptionContentModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStoreSubscriptionContentModelMasterDomain>& Self,
        const Request::FDeleteStoreSubscriptionContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreSubscriptionContentModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithContentName(Self->ContentName);
        const auto Future = Self->Client->DeleteStoreSubscriptionContentModelMaster(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "StoreSubscriptionContentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FDeleteTask>> FStoreSubscriptionContentModelMasterDomain::Delete(
        Request::FDeleteStoreSubscriptionContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FStoreSubscriptionContentModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ContentName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ContentName.IsSet() ? *ContentName : "null") + ":" +
            ChildType;
    }

    FString FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
        TOptional<FString> ContentName
    )
    {
        return FString("") +
            (ContentName.IsSet() ? *ContentName : "null");
    }

    FStoreSubscriptionContentModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FStoreSubscriptionContentModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreSubscriptionContentModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster>(
            Self->ParentKey,
            Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
                Self->ContentName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Money2::Request::FGetStoreSubscriptionContentModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
                    Self->ContentName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "storeSubscriptionContentModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster>(
                Self->ParentKey,
                Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
                    Self->ContentName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FModelTask>> FStoreSubscriptionContentModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStoreSubscriptionContentModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
                ContentName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster>(obj));
            }
        );
    }

    void FStoreSubscriptionContentModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
                ContentName
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

