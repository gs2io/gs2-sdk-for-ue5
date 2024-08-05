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

#include "Account/Domain/Model/TakeOverTypeModelMaster.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/PlatformIdAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"
#include "Account/Domain/Model/TakeOverTypeModel.h"
#include "Account/Domain/Model/TakeOverTypeModelMaster.h"
#include "Account/Domain/Model/CurrentModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Account::Domain::Model
{

    FTakeOverTypeModelMasterDomain::FTakeOverTypeModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<int32> Type
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Type(Type),
        ParentKey(Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "TakeOverTypeModelMaster"
        ))
    {
    }

    FTakeOverTypeModelMasterDomain::FTakeOverTypeModelMasterDomain(
        const FTakeOverTypeModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Type(From.Type),
        ParentKey(From.ParentKey)
    {

    }

    FTakeOverTypeModelMasterDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FTakeOverTypeModelMasterDomain>& Self,
        const Request::FCreateTakeOverTypeModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverTypeModelMasterDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelMasterDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithType(Self->Type);
        const auto Future = Self->Client->CreateTakeOverTypeModelMaster(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "TakeOverTypeModelMaster"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FTakeOverTypeModelMasterDomain::FCreateTask>> FTakeOverTypeModelMasterDomain::Create(
        Request::FCreateTakeOverTypeModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FTakeOverTypeModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FTakeOverTypeModelMasterDomain>& Self,
        const Request::FGetTakeOverTypeModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverTypeModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOverTypeModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithType(Self->Type);
        const auto Future = Self->Client->GetTakeOverTypeModelMaster(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "TakeOverTypeModelMaster"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FTakeOverTypeModelMasterDomain::FGetTask>> FTakeOverTypeModelMasterDomain::Get(
        Request::FGetTakeOverTypeModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FTakeOverTypeModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FTakeOverTypeModelMasterDomain>& Self,
        const Request::FUpdateTakeOverTypeModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverTypeModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithType(Self->Type);
        const auto Future = Self->Client->UpdateTakeOverTypeModelMaster(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "TakeOverTypeModelMaster"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FTakeOverTypeModelMasterDomain::FUpdateTask>> FTakeOverTypeModelMasterDomain::Update(
        Request::FUpdateTakeOverTypeModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FTakeOverTypeModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FTakeOverTypeModelMasterDomain>& Self,
        const Request::FDeleteTakeOverTypeModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverTypeModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithType(Self->Type);
        const auto Future = Self->Client->DeleteTakeOverTypeModelMaster(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "TakeOverTypeModelMaster"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Delete(Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverTypeModelMasterDomain::FDeleteTask>> FTakeOverTypeModelMasterDomain::Delete(
        Request::FDeleteTakeOverTypeModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FTakeOverTypeModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> Type,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Type.IsSet() ? *Type : "null") + ":" +
            ChildType;
    }

    FString FTakeOverTypeModelMasterDomain::CreateCacheKey(
        TOptional<FString> Type
    )
    {
        return FString("") +
            (Type.IsSet() ? *Type : "null");
    }

    FTakeOverTypeModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FTakeOverTypeModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FTakeOverTypeModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOverTypeModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Account::Model::FTakeOverTypeModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Account::Model::FTakeOverTypeModelMaster>(
            Self->ParentKey,
            Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain::CreateCacheKey(
                Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Account::Request::FGetTakeOverTypeModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "takeOverTypeModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Account::Model::FTakeOverTypeModelMaster>(
                Self->ParentKey,
                Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverTypeModelMasterDomain::FModelTask>> FTakeOverTypeModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTakeOverTypeModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FTakeOverTypeModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FTakeOverTypeModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain::CreateCacheKey(
                Type.IsSet() ? FString::FromInt(*Type) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FTakeOverTypeModelMaster>(obj));
            }
        );
    }

    void FTakeOverTypeModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain::CreateCacheKey(
                Type.IsSet() ? FString::FromInt(*Type) : TOptional<FString>()
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

