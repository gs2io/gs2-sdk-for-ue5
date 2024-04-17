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

#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Account::Domain::Model
{

    FTakeOverDomain::FTakeOverDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<int32> Type
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        Type(Type),
        ParentKey(Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "TakeOver"
        ))
    {
    }

    FTakeOverDomain::FTakeOverDomain(
        const FTakeOverDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        Type(From.Type),
        ParentKey(From.ParentKey)
    {

    }

    FTakeOverDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FTakeOverDomain>& Self,
        const Request::FCreateTakeOverByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithType(Self->Type);
        const auto Future = Self->Client->CreateTakeOverByUserId(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "TakeOver"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FTakeOver::TypeName,
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

    TSharedPtr<FAsyncTask<FTakeOverDomain::FCreateTask>> FTakeOverDomain::Create(
        Request::FCreateTakeOverByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FTakeOverDomain::FGetTask::FGetTask(
        const TSharedPtr<FTakeOverDomain>& Self,
        const Request::FGetTakeOverByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithType(Self->Type);
        const auto Future = Self->Client->GetTakeOverByUserId(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "TakeOver"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FTakeOver::TypeName,
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

    TSharedPtr<FAsyncTask<FTakeOverDomain::FGetTask>> FTakeOverDomain::Get(
        Request::FGetTakeOverByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FTakeOverDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FTakeOverDomain>& Self,
        const Request::FUpdateTakeOverByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithType(Self->Type);
        const auto Future = Self->Client->UpdateTakeOverByUserId(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "TakeOver"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FTakeOver::TypeName,
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

    TSharedPtr<FAsyncTask<FTakeOverDomain::FUpdateTask>> FTakeOverDomain::Update(
        Request::FUpdateTakeOverByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FString FTakeOverDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> Type,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Type.IsSet() ? *Type : "null") + ":" +
            ChildType;
    }

    FString FTakeOverDomain::CreateCacheKey(
        TOptional<FString> Type
    )
    {
        return FString("") +
            (Type.IsSet() ? *Type : "null");
    }

    FTakeOverDomain::FModelTask::FModelTask(
        const TSharedPtr<FTakeOverDomain> Self
    ): Self(Self)
    {

    }

    FTakeOverDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Account::Model::FTakeOver> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Account::Model::FTakeOver>(
            Self->ParentKey,
            Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Account::Request::FGetTakeOverByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FTakeOver::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "takeOver")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Account::Model::FTakeOver>(
                Self->ParentKey,
                Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverDomain::FModelTask>> FTakeOverDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTakeOverDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FTakeOverDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FTakeOverPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                Type.IsSet() ? FString::FromInt(*Type) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FTakeOver>(obj));
            }
        );
    }

    void FTakeOverDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
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

