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

#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Output.h"
#include "Freeze/Model/Cache/Stage.h"
#include "Freeze/Model/Cache/Output.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Freeze::Domain::Model
{

    FStageDomain::FStageDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Freeze::Domain::FGs2FreezeDomainPtr& Service,
        const TOptional<FString> StageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Freeze::FGs2FreezeRestClient>(Gs2->RestSession)),
        StageName(StageName),
        ParentKey(Gs2::Freeze::Model::Cache::FStageCache::CreateCacheParentKey())
    {
    }

    FStageDomain::FStageDomain(
        const FStageDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StageName(From.StageName),
        ParentKey(From.ParentKey)
    {

    }

    FStageDomain::FGetTask::FGetTask(
        const TSharedPtr<FStageDomain>& Self,
        const Request::FGetStageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStageDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FStage>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStageName(Self->StageName);
        const auto Future = Self->Client->GetStage(
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

    TSharedPtr<FAsyncTask<FStageDomain::FGetTask>> FStageDomain::Get(
        Request::FGetStageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStageDomain::FPromoteTask::FPromoteTask(
        const TSharedPtr<FStageDomain>& Self,
        const Request::FPromoteStageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStageDomain::FPromoteTask::FPromoteTask(
        const FPromoteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FPromoteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStageName(Self->StageName);
        const auto Future = Self->Client->PromoteStage(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
                ResultModel->GetItem()->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Freeze::Model::FStage::TypeName,
                Self->ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStageDomain::FPromoteTask>> FStageDomain::Promote(
        Request::FPromoteStageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPromoteTask>>(this->AsShared(), Request);
    }

    FStageDomain::FRollbackTask::FRollbackTask(
        const TSharedPtr<FStageDomain>& Self,
        const Request::FRollbackStageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStageDomain::FRollbackTask::FRollbackTask(
        const FRollbackTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FRollbackTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStageName(Self->StageName);
        const auto Future = Self->Client->RollbackStage(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
                ResultModel->GetItem()->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Freeze::Model::FStage::TypeName,
                Self->ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStageDomain::FRollbackTask>> FStageDomain::Rollback(
        Request::FRollbackStageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRollbackTask>>(this->AsShared(), Request);
    }

    Gs2::Freeze::Domain::Iterator::FDescribeOutputsIteratorPtr FStageDomain::Outputs(
    ) const
    {
        return MakeShared<Gs2::Freeze::Domain::Iterator::FDescribeOutputsIterator>(
            Gs2,
            Client,
            StageName
        );
    }

    Gs2::Core::Domain::CallbackID FStageDomain::SubscribeOutputs(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Freeze::Model::FOutput::TypeName,
            Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(
                StageName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }

    Gs2::Core::Domain::CallbackID FStageDomain::SubscribeOutputs(
        TFunction<void(TArray<Gs2::Freeze::Model::FOutputPtr>)> Callback
    )
    {
        const TWeakPtr<FStageDomain> WeakSelf = AsShared();
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Freeze::Model::FOutput::TypeName,
            Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(
                StageName,
                TOptional<int32>()
            ),
            [Callback](const TArray<FGs2ObjectPtr>& Objects)
            {
                TArray<Gs2::Freeze::Model::FOutputPtr> Items;
                for (const auto& Object : Objects)
                {
                    if (Object)
                    {
                        Items.Add(StaticCastSharedPtr<Gs2::Freeze::Model::FOutput>(Object));
                    }
                }
                Callback(Items);
            },
            [WeakSelf]()
            {
                const auto Self = WeakSelf.Pin();
                if (!Self.IsValid()) return;
                auto Iterator = Self->Outputs()->begin();
                while (Iterator.HasNext())
                {
                    ++Iterator;
                }
            }
        );
    }

    void FStageDomain::UnsubscribeOutputs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Freeze::Model::FOutput::TypeName,
            Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(
                StageName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }

    FStageDomain::FSubscribeOutputsWithInitialCallTask::FSubscribeOutputsWithInitialCallTask(
        const TSharedPtr<FStageDomain> Self,
        const TFunction<void(TArray<Gs2::Freeze::Model::FOutputPtr>)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FStageDomain::FSubscribeOutputsWithInitialCallTask::FSubscribeOutputsWithInitialCallTask(
        const FSubscribeOutputsWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FSubscribeOutputsWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        TArray<Gs2::Freeze::Model::FOutputPtr> Items;
        auto Iterator = Self->Outputs()->begin();
        while (Iterator.HasNext())
        {
            if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
            ++Iterator;
        }
        if (Iterator.IsError())
        {
            return Iterator.Error();
        }
        const auto ID = Self->SubscribeOutputs(Callback);
        Callback(Items);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStageDomain::FSubscribeOutputsWithInitialCallTask>> FStageDomain::SubscribeOutputsWithInitialCall(
        TFunction<void(TArray<Gs2::Freeze::Model::FOutputPtr>)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeOutputsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Freeze::Domain::Model::FOutputDomain> FStageDomain::Output(
        const FString OutputName
    )
    {
        return MakeShared<Gs2::Freeze::Domain::Model::FOutputDomain>(
            Gs2,
            Service,
            StageName,
            OutputName == TEXT("") ? TOptional<FString>() : TOptional<FString>(OutputName)
        );
    }

    FString FStageDomain::CreateCacheParentKey(
        TOptional<FString> StageName,
        FString ChildType
    )
    {
        return FString("") +
            (StageName.IsSet() ? *StageName : "null") + ":" +
            ChildType;
    }

    FString FStageDomain::CreateCacheKey(
        TOptional<FString> StageName
    )
    {
        return FString("") +
            (StageName.IsSet() ? *StageName : "null");
    }

    FStageDomain::FModelTask::FModelTask(
        const TSharedPtr<FStageDomain> Self
    ): Self(Self)
    {

    }

    FStageDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FStage>> Result
    )
    {
        const auto ParentKey = Gs2::Freeze::Model::Cache::FStageCache::CreateCacheParentKey();
        const FString CacheKey = Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
            Self->StageName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Freeze::Model::FStage::TypeName,
            ParentKey,
            CacheKey,
            [this, Result, CacheKey, ParentKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Freeze::Model::FStage> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Freeze::Model::FStage>(
                    ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Freeze::Request::FGetStageRequest>()
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
                            Gs2::Freeze::Model::FStage::TypeName,
                            ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "stage")
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
                        Gs2::Freeze::Model::FStage::TypeName,
                        ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Freeze::Model::FStage::TypeName,
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

    TSharedPtr<FAsyncTask<FStageDomain::FModelTask>> FStageDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStageDomain::FModelTask>>(this->AsShared());
    }

    FStageDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FStageDomain> Self,
        const TFunction<void(Gs2::Freeze::Model::FStagePtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FStageDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FStageDomain::FSubscribeWithInitialCallTask>> FStageDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Freeze::Model::FStagePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FStageDomain::Invalidate()
    {
        Gs2::Freeze::Model::Cache::FStageCache::Delete(
            Gs2->Cache,
            StageName,
            TOptional<int32>()
        );
    }

    void FStageDomain::InvalidateOutputs()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Freeze::Model::FOutput::TypeName,
            Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(
                StageName,
                TOptional<int32>()
            )
        );
    }

    Gs2::Core::Domain::CallbackID FStageDomain::Subscribe(
        TFunction<void(Gs2::Freeze::Model::FStagePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            ParentKey,
            Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
                StageName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Freeze::Model::FStage>(obj));
            }
        );
    }

    void FStageDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            ParentKey,
            Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
                StageName
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
