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

#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/Expression.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"
#include "Distributor/Domain/Model/TransactionResult.h"
#include "Distributor/Domain/Model/TransactionResultAccessToken.h"
#include "Distributor/Model/Cache/StampSheetResult.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Distributor::Domain::Model
{

    FStampSheetResultDomain::FStampSheetResultDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> TransactionId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        TransactionId(TransactionId),
        ParentKey(Gs2::Distributor::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "StampSheetResult"
        ))
    {
    }

    FStampSheetResultDomain::FStampSheetResultDomain(
        const FStampSheetResultDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        TransactionId(From.TransactionId),
        ParentKey(From.ParentKey)
    {

    }

    FStampSheetResultDomain::FGetTask::FGetTask(
        const TSharedPtr<FStampSheetResultDomain>& Self,
        const Request::FGetStampSheetResultByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStampSheetResultDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetResultDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithTransactionId(Self->TransactionId);
        const auto Future = Self->Client->GetStampSheetResultByUserId(
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
              }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Distributor::Model::Cache::FStampSheetResultCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetTransactionId(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStampSheetResultDomain::FGetTask>> FStampSheetResultDomain::Get(
        Request::FGetStampSheetResultByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FStampSheetResultDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> TransactionId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (TransactionId.IsSet() ? *TransactionId : "null") + ":" +
            ChildType;
    }

    FString FStampSheetResultDomain::CreateCacheKey(
        TOptional<FString> TransactionId
    )
    {
        return FString("") +
            (TransactionId.IsSet() ? *TransactionId : "null");
    }

    FStampSheetResultDomain::FModelTask::FModelTask(
        const TSharedPtr<FStampSheetResultDomain> Self
    ): Self(Self)
    {

    }

    FStampSheetResultDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetResultDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
    )
    {
        const FString CacheKey = Gs2::Distributor::Domain::Model::FStampSheetResultDomain::CreateCacheKey(
            Self->TransactionId
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Distributor::Model::FStampSheetResult::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Distributor::Model::FStampSheetResult> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Distributor::Model::FStampSheetResult>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Distributor::Request::FGetStampSheetResultByUserIdRequest>()
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
                            Gs2::Distributor::Model::FStampSheetResult::TypeName,
                            Self->ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "stampSheetResult")
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
                        Gs2::Distributor::Model::FStampSheetResult::TypeName,
                        Self->ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Distributor::Model::FStampSheetResult::TypeName,
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

    TSharedPtr<FAsyncTask<FStampSheetResultDomain::FModelTask>> FStampSheetResultDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStampSheetResultDomain::FModelTask>>(this->AsShared());
    }

    FStampSheetResultDomain::FModelNoCacheTask::FModelNoCacheTask(
        const TSharedPtr<FStampSheetResultDomain> Self
    ):
        Self(Self)
    {
    }

    FStampSheetResultDomain::FModelNoCacheTask::FModelNoCacheTask(
        const FModelNoCacheTask& From
    ):
        Self(From.Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetResultDomain::FModelNoCacheTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
    )
    {
        TSharedPtr<Gs2::Distributor::Model::FStampSheetResult> Value;
        const auto Future = Self->Get(
            MakeShared<Gs2::Distributor::Request::FGetStampSheetResultByUserIdRequest>()
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
            {
                return Future->GetTask().Error();
            }

            const auto Key = Gs2::Distributor::Domain::Model::FStampSheetResultDomain::CreateCacheKey(
                Self->TransactionId
            );
            Self->Gs2->Cache->Put(
                Gs2::Distributor::Model::FStampSheetResult::TypeName,
                Self->ParentKey,
                Key,
                nullptr,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );

            if (Future->GetTask().Error()->Detail(0)->GetComponent() != "stampSheetResult")
            {
                return Future->GetTask().Error();
            }
        }
        else
        {
            Value = Future->GetTask().Result();
            if (Value.IsValid())
            {
                Self->Gs2->Cache->Put(
                    Gs2::Distributor::Model::FStampSheetResult::TypeName,
                    Self->ParentKey,
                    FStampSheetResultDomain::CreateCacheKey(
                        Self->TransactionId
                    ),
                    Value,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        Future->EnsureCompletion();
        *Result = Value;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStampSheetResultDomain::FModelNoCacheTask>> FStampSheetResultDomain::ModelNoCache()
    {
        return Gs2::Core::Util::New<FAsyncTask<FStampSheetResultDomain::FModelNoCacheTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStampSheetResultDomain::Subscribe(
        TFunction<void(Gs2::Distributor::Model::FStampSheetResultPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Distributor::Model::Cache::FStampSheetResultCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Distributor::Model::Cache::FStampSheetResultCache::CreateCacheKey(

            TransactionId
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Distributor::Domain::FGs2DistributorDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryTransactionId = TransactionId;
        return Gs2->Cache->Subscribe(
            Gs2::Distributor::Model::FStampSheetResult::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Distributor::Model::FStampSheetResult>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryTransactionId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FStampSheetResultDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryTransactionId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FStampSheetResultDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Distributor::Model::Cache::FStampSheetResultCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Distributor::Model::Cache::FStampSheetResultCache::CreateCacheKey(

            TransactionId
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Distributor::Model::FStampSheetResult::TypeName,
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
