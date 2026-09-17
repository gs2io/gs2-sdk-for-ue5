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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"

#include "Identifier/Model/Cache/Identifier.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Identifier::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
        const TOptional<FString> UserName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Gs2->RestSession)),
        UserName(UserName),
        ParentKey("identifier:User")
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        UserName(From.UserName),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FUpdateUserRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->UpdateUser(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto UserName = Self->UserName;
        if (ResultModel->GetItem() != nullptr && ResultModel->GetItem()->GetName().IsSet())
        {
            UserName = ResultModel->GetItem()->GetName();
        }
        if (ResultModel->GetItem() != nullptr && !ResultModel->GetItem()->GetName().IsSet() && UserName.IsSet())
        {
            ResultModel->GetItem()->WithName(UserName);
        }
        if (ResultModel->GetItem() != nullptr)
        {
            Self->Gs2->Cache->Put(
                Gs2::Identifier::Model::FUser::TypeName,
                Self->ParentKey,
                Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                    UserName
                ),
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        Self->Gs2->Cache->ClearListCache(
            Gs2::Identifier::Model::FUser::TypeName,
            Self->ParentKey
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FUpdateTask>> FUserDomain::Update(
        Request::FUpdateUserRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FUserDomain::FGetTask::FGetTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FGetUserRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FUser>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->GetUser(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FGetTask>> FUserDomain::Get(
        Request::FGetUserRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FUserDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FDeleteUserRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->DeleteUser(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (Self->UserName.IsSet())
        {
            Self->Gs2->Cache->Delete(
                Gs2::Identifier::Model::FUser::TypeName,
                Self->ParentKey,
                Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                    Self->UserName
                )
            );
        }
        Self->Gs2->Cache->ClearListCache(
            Gs2::Identifier::Model::FUser::TypeName,
            Self->ParentKey
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FDeleteTask>> FUserDomain::Delete(
        Request::FDeleteUserRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FUserDomain::FCreateIdentifierTask::FCreateIdentifierTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FCreateIdentifierRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FCreateIdentifierTask::FCreateIdentifierTask(
        const FCreateIdentifierTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FCreateIdentifierTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FIdentifierDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->CreateIdentifier(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        auto Domain = MakeShared<Gs2::Identifier::Domain::Model::FIdentifierDomain>(
            Self->Gs2,
            Self->Service,
            ResultModel->GetItem()->GetUserName(),
            ResultModel->GetItem()->GetClientId()
        );
        if (ResultModel != nullptr)
        {
            Domain->ClientSecret = *ResultModel->GetClientSecret();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FCreateIdentifierTask>> FUserDomain::CreateIdentifier(
        Request::FCreateIdentifierRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateIdentifierTask>>(this->AsShared(), Request);
    }

    Gs2::Identifier::Domain::Iterator::FDescribeIdentifiersIteratorPtr FUserDomain::Identifiers(
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Iterator::FDescribeIdentifiersIterator>(
            Gs2,
            Client,
            UserName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeIdentifiers(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Identifier::Model::FIdentifier::TypeName,
            Gs2::Identifier::Model::Cache::FIdentifierCache::CreateCacheParentKey(
                UserName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeIdentifiers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Identifier::Model::FIdentifier::TypeName,
            Gs2::Identifier::Model::Cache::FIdentifierCache::CreateCacheParentKey(
                UserName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectIdentifiersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Identifier::Model::FIdentifierPtr>>, public TSharedFromThis<FCollectIdentifiersTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Identifier::Model::FIdentifierPtr>)> OnCollected;

    public:
        explicit FCollectIdentifiersTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Identifier::Model::FIdentifierPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectIdentifiersTask(const FCollectIdentifiersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Identifier::Model::FIdentifierPtr>>> Result) override
        {
            TArray<Gs2::Identifier::Model::FIdentifierPtr> Items;
            auto Iterator = Self->Identifiers()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Identifier::Model::FIdentifierPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeIdentifiers(
        TFunction<void(TArray<Gs2::Identifier::Model::FIdentifierPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Identifier::Domain::FGs2IdentifierDomain> WeakService = this->Service;
        const auto QueryUserName = UserName;
        const auto Parent = Gs2::Identifier::Model::Cache::FIdentifierCache::CreateCacheParentKey(
        UserName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Identifier::Model::FIdentifier::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Identifier::Model::FIdentifierPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Identifier::Model::FIdentifier>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryUserName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryUserName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectIdentifiersTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateIdentifiers()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Identifier::Model::FIdentifier::TypeName,
            Gs2::Identifier::Model::Cache::FIdentifierCache::CreateCacheParentKey(
        UserName,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeIdentifiersWithInitialCallTask::FSubscribeIdentifiersWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Identifier::Model::FIdentifierPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserDomain::FSubscribeIdentifiersWithInitialCallTask::FSubscribeIdentifiersWithInitialCallTask(const FSubscribeIdentifiersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeIdentifiersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectIdentifiersTask>>(Self, TFunction<void(TArray<Gs2::Identifier::Model::FIdentifierPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeIdentifiers(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeIdentifiersWithInitialCallTask>> FUserDomain::SubscribeIdentifiersWithInitialCall(TFunction<void(TArray<Gs2::Identifier::Model::FIdentifierPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeIdentifiersWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Identifier::Domain::Model::FIdentifierDomain> FUserDomain::Identifier(
        const FString ClientId
    )
    {
        return MakeShared<Gs2::Identifier::Domain::Model::FIdentifierDomain>(
            Gs2,
            Service,
            UserName,
            ClientId == TEXT("") ? TOptional<FString>() : TOptional<FString>(ClientId)
        );
    }

    TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain> FUserDomain::Password(
    )
    {
        return MakeShared<Gs2::Identifier::Domain::Model::FPasswordDomain>(
            Gs2,
            Service,
            UserName
        );
    }

    TSharedPtr<Gs2::Identifier::Domain::Model::FAttachSecurityPolicyDomain> FUserDomain::AttachSecurityPolicy(
    )
    {
        return MakeShared<Gs2::Identifier::Domain::Model::FAttachSecurityPolicyDomain>(
            Gs2,
            Service,
            UserName
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> UserName,
        FString ChildType
    )
    {
        return FString("") +
            (UserName.IsSet() ? *UserName : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserName
    )
    {
        return FString("") +
            (UserName.IsSet() ? *UserName : "null");
    }

    FUserDomain::FModelTask::FModelTask(
        const TSharedPtr<FUserDomain> Self
    ): Self(Self)
    {

    }

    FUserDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FUser>> Result
    )
    {
        const auto ParentKey = FString("identifier:User");
        const FString CacheKey = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
            Self->UserName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Identifier::Model::FUser::TypeName,
            ParentKey,
            CacheKey,
            [this, Result, CacheKey, ParentKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Identifier::Model::FUser> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Identifier::Model::FUser>(
                    ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Identifier::Request::FGetUserRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }
                        Self->Gs2->Cache->Put(
                            Gs2::Identifier::Model::FUser::TypeName,
                            ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "user")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                    }
                    Future->EnsureCompletion();
                }
                if (!bCacheHit)
                {
                    FGs2ObjectPtr ExistingObject;
                    const bool Existing = Self->Gs2->Cache->TryGet(
                        Gs2::Identifier::Model::FUser::TypeName,
                        ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Identifier::Model::FUser::TypeName,
                            ParentKey,
                            CacheKey,
                            Value,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }

                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FUserDomain::FModelTask>> FUserDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FUserDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FUserDomain::Subscribe(
        TFunction<void(Gs2::Identifier::Model::FUserPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Identifier::Domain::FGs2IdentifierDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryUserName = UserName;
        return Gs2->Cache->Subscribe(
            Gs2::Identifier::Model::FUser::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                UserName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Identifier::Model::FUser>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryUserName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FUserDomain>(
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

    void FUserDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Identifier::Model::FUser::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                UserName
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

