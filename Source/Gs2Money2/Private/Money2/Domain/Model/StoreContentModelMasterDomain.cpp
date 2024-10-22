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

#include "Money2/Domain/Model/StoreContentModelMaster.h"
#include "Money2/Domain/Model/Namespace.h"
#include "Money2/Domain/Model/User.h"
#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Domain/Model/Wallet.h"
#include "Money2/Domain/Model/WalletAccessToken.h"
#include "Money2/Domain/Model/Event.h"
#include "Money2/Domain/Model/EventAccessToken.h"
#include "Money2/Domain/Model/StoreContentModel.h"
#include "Money2/Domain/Model/StoreContentModelMaster.h"
#include "Money2/Domain/Model/CurrentModelMaster.h"
#include "Money2/Domain/Model/DailyTransactionHistory.h"
#include "Money2/Domain/Model/UnusedBalance.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FStoreContentModelMasterDomain::FStoreContentModelMasterDomain(
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
            "StoreContentModelMaster"
        ))
    {
    }

    FStoreContentModelMasterDomain::FStoreContentModelMasterDomain(
        const FStoreContentModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ContentName(From.ContentName),
        ParentKey(From.ParentKey)
    {

    }

    FStoreContentModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FStoreContentModelMasterDomain>& Self,
        const Request::FGetStoreContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStoreContentModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreContentModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FStoreContentModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithContentName(Self->ContentName);
        const auto Future = Self->Client->GetStoreContentModelMaster(
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
                    "StoreContentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FStoreContentModelMasterDomain::FGetTask>> FStoreContentModelMasterDomain::Get(
        Request::FGetStoreContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStoreContentModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FStoreContentModelMasterDomain>& Self,
        const Request::FUpdateStoreContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStoreContentModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreContentModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithContentName(Self->ContentName);
        const auto Future = Self->Client->UpdateStoreContentModelMaster(
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
                    "StoreContentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FStoreContentModelMasterDomain::FUpdateTask>> FStoreContentModelMasterDomain::Update(
        Request::FUpdateStoreContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FStoreContentModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStoreContentModelMasterDomain>& Self,
        const Request::FDeleteStoreContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStoreContentModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreContentModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithContentName(Self->ContentName);
        const auto Future = Self->Client->DeleteStoreContentModelMaster(
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
                    "StoreContentModelMaster"
                );
                const auto Key = Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Money2::Model::FStoreContentModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStoreContentModelMasterDomain::FDeleteTask>> FStoreContentModelMasterDomain::Delete(
        Request::FDeleteStoreContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FStoreContentModelMasterDomain::CreateCacheParentKey(
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

    FString FStoreContentModelMasterDomain::CreateCacheKey(
        TOptional<FString> ContentName
    )
    {
        return FString("") +
            (ContentName.IsSet() ? *ContentName : "null");
    }

    FStoreContentModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FStoreContentModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FStoreContentModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreContentModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FStoreContentModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money2::Model::FStoreContentModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FStoreContentModelMaster>(
            Self->ParentKey,
            Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain::CreateCacheKey(
                Self->ContentName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Money2::Request::FGetStoreContentModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain::CreateCacheKey(
                    Self->ContentName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "storeContentModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FStoreContentModelMaster>(
                Self->ParentKey,
                Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain::CreateCacheKey(
                    Self->ContentName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStoreContentModelMasterDomain::FModelTask>> FStoreContentModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStoreContentModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStoreContentModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FStoreContentModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain::CreateCacheKey(
                ContentName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FStoreContentModelMaster>(obj));
            }
        );
    }

    void FStoreContentModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain::CreateCacheKey(
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

