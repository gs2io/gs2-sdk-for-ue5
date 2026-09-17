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

#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"
#include "Identifier/Model/Cache/Password.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Identifier::Domain::Model
{

    FPasswordDomain::FPasswordDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
        const TOptional<FString> UserName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Gs2->RestSession)),
        UserName(UserName),
        ParentKey(Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
            UserName,
            "Password"
        ))
    {
    }

    FPasswordDomain::FPasswordDomain(
        const FPasswordDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        UserName(From.UserName),
        ParentKey(From.ParentKey)
    {

    }

    FPasswordDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FCreatePasswordRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->CreatePassword(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Identifier::Model::Cache::FPasswordCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetUserName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FCreateTask>> FPasswordDomain::Create(
        Request::FCreatePasswordRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FGetTask::FGetTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FGetPasswordRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FPassword>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->GetPassword(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Identifier::Model::Cache::FPasswordCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetUserName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FGetTask>> FPasswordDomain::Get(
        Request::FGetPasswordRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FEnableMfaTask::FEnableMfaTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FEnableMfaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FEnableMfaTask::FEnableMfaTask(
        const FEnableMfaTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FEnableMfaTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->EnableMfa(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Identifier::Model::Cache::FPasswordCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetUserName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetChallengeToken().IsSet())
            {
                Domain->ChallengeToken = *ResultModel->GetChallengeToken();
            }
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FEnableMfaTask>> FPasswordDomain::EnableMfa(
        Request::FEnableMfaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEnableMfaTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FChallengeMfaTask::FChallengeMfaTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FChallengeMfaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FChallengeMfaTask::FChallengeMfaTask(
        const FChallengeMfaTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FChallengeMfaTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->ChallengeMfa(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Identifier::Model::Cache::FPasswordCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetUserName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FChallengeMfaTask>> FPasswordDomain::ChallengeMfa(
        Request::FChallengeMfaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FChallengeMfaTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FDisableMfaTask::FDisableMfaTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FDisableMfaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FDisableMfaTask::FDisableMfaTask(
        const FDisableMfaTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FDisableMfaTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->DisableMfa(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Identifier::Model::Cache::FPasswordCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetUserName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FDisableMfaTask>> FPasswordDomain::DisableMfa(
        Request::FDisableMfaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDisableMfaTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FDeletePasswordRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->DeletePassword(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

              if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::Identifier::Model::Cache::FPasswordCache::Delete(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetUserName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FDeleteTask>> FPasswordDomain::Delete(
        Request::FDeletePasswordRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FPasswordDomain::CreateCacheParentKey(
        TOptional<FString> UserName,
        FString ChildType
    )
    {
        return FString("") +
            (UserName.IsSet() ? *UserName : "null") + ":" +
            ChildType;
    }

    FString FPasswordDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FPasswordDomain::FModelTask::FModelTask(
        const TSharedPtr<FPasswordDomain> Self
    ): Self(Self)
    {

    }

    FPasswordDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FPassword>> Result
    )
    {
        const auto CacheParentKey = Gs2::Identifier::Model::Cache::FPasswordCache::CreateCacheParentKey(

            Self->UserName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Identifier::Model::Cache::FPasswordCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Identifier::Model::FPassword::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Identifier::Model::FPasswordPtr Value;
                const auto CacheHit = Gs2::Identifier::Model::Cache::FPasswordCache::TryGet(
                    Self->Gs2->Cache,

                    Self->UserName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Identifier::Model::Cache::FPasswordCache::Fetch(
                    Self->Gs2->Cache,

                    Self->UserName,
                    TOptional<int32>(),
                    [Self](Gs2::Identifier::Model::FPasswordPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Identifier::Request::FGetPasswordRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FModelTask>> FPasswordDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPasswordDomain::FModelTask>>(this->AsShared());
    }

    void FPasswordDomain::Invalidate()
    {
        Gs2::Identifier::Model::Cache::FPasswordCache::Delete(
            Gs2->Cache,

            UserName,
            TOptional<int32>()
        );
    }

    FPasswordDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FPasswordDomain>& Self,
        TFunction<void(Gs2::Identifier::Model::FPasswordPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FPasswordDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FSubscribeWithInitialCallTask>> FPasswordDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Identifier::Model::FPasswordPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FPasswordDomain::Subscribe(
        TFunction<void(Gs2::Identifier::Model::FPasswordPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Identifier::Model::Cache::FPasswordCache::CreateCacheParentKey(

            UserName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Identifier::Model::Cache::FPasswordCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Identifier::Domain::FGs2IdentifierDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryUserName = UserName;
        return Gs2->Cache->Subscribe(
            Gs2::Identifier::Model::FPassword::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Identifier::Model::FPassword>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryUserName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FPasswordDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryUserName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FPasswordDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Identifier::Model::Cache::FPasswordCache::CreateCacheParentKey(

            UserName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Identifier::Model::Cache::FPasswordCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Identifier::Model::FPassword::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
