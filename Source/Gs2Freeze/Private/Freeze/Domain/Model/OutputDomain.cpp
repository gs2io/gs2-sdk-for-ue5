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

#include "Freeze/Domain/Model/Output.h"
#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Output.h"
#include "Freeze/Model/Cache/Output.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Freeze::Domain::Model
{

    FOutputDomain::FOutputDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Freeze::Domain::FGs2FreezeDomainPtr& Service,
        const TOptional<FString> StageName,
        const TOptional<FString> OutputName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Freeze::FGs2FreezeRestClient>(Gs2->RestSession)),
        StageName(StageName),
        OutputName(OutputName),
        ParentKey(Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(
            StageName,
            TOptional<int32>()
        ))
    {
    }

    FOutputDomain::FOutputDomain(
        const FOutputDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StageName(From.StageName),
        OutputName(From.OutputName),
        ParentKey(From.ParentKey)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const TSharedPtr<FOutputDomain>& Self,
        const Request::FGetOutputRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FOutput>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStageName(Self->StageName)
            ->WithOutputName(Self->OutputName);
        const auto Future = Self->Client->GetOutput(
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

    TSharedPtr<FAsyncTask<FOutputDomain::FGetTask>> FOutputDomain::Get(
        Request::FGetOutputRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FOutputDomain::CreateCacheParentKey(
        TOptional<FString> StageName,
        TOptional<FString> OutputName,
        FString ChildType
    )
    {
        return FString("") +
            (StageName.IsSet() ? *StageName : "null") + ":" +
            (OutputName.IsSet() ? *OutputName : "null") + ":" +
            ChildType;
    }

    FString FOutputDomain::CreateCacheKey(
        TOptional<FString> OutputName
    )
    {
        return FString("") +
            (OutputName.IsSet() ? *OutputName : "null");
    }

    FOutputDomain::FModelTask::FModelTask(
        const TSharedPtr<FOutputDomain> Self
    ): Self(Self)
    {

    }

    FOutputDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FOutput>> Result
    )
    {
        const FString CacheKey = Gs2::Freeze::Domain::Model::FOutputDomain::CreateCacheKey(
            Self->OutputName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Freeze::Model::FOutput::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Freeze::Model::FOutput> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Freeze::Model::FOutput>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Freeze::Request::FGetOutputRequest>()
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
                            Gs2::Freeze::Model::FOutput::TypeName,
                            Self->ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "output")
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
                        Gs2::Freeze::Model::FOutput::TypeName,
                        Self->ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Freeze::Model::FOutput::TypeName,
                            Self->ParentKey,
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

    TSharedPtr<FAsyncTask<FOutputDomain::FModelTask>> FOutputDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FOutputDomain::FModelTask>>(this->AsShared());
    }

    FOutputDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FOutputDomain> Self,
        const TFunction<void(Gs2::Freeze::Model::FOutputPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FOutputDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FOutputDomain::FSubscribeWithInitialCallTask>> FOutputDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Freeze::Model::FOutputPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FOutputDomain::Invalidate()
    {
        Gs2::Freeze::Model::Cache::FOutputCache::Delete(
            Gs2->Cache,
            StageName,
            OutputName,
            TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FOutputDomain::Subscribe(
        TFunction<void(Gs2::Freeze::Model::FOutputPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(

            StageName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheKey(

            OutputName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Freeze::Domain::FGs2FreezeDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryStageName = StageName;
        const TOptional<FString> QueryOutputName = OutputName;
        return Gs2->Cache->Subscribe(
            Gs2::Freeze::Model::FOutput::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Freeze::Model::FOutput>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryStageName, QueryOutputName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FOutputDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryStageName,
                    QueryOutputName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FOutputDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(

            StageName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheKey(

            OutputName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Freeze::Model::FOutput::TypeName,
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
