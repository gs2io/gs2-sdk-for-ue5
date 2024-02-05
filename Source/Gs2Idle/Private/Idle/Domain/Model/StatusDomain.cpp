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

#include "Idle/Domain/Model/Status.h"
#include "Idle/Domain/Model/Namespace.h"
#include "Idle/Domain/Model/CategoryModelMaster.h"
#include "Idle/Domain/Model/CategoryModel.h"
#include "Idle/Domain/Model/User.h"
#include "Idle/Domain/Model/UserAccessToken.h"
#include "Idle/Domain/Model/Status.h"
#include "Idle/Domain/Model/StatusAccessToken.h"
#include "Idle/Domain/Model/CurrentCategoryMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Idle::Domain::Model
{

    FStatusDomain::FStatusDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Idle::Domain::FGs2IdleDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> CategoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Idle::FGs2IdleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        CategoryName(CategoryName),
        ParentKey(Gs2::Idle::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Status"
        ))
    {
    }

    FStatusDomain::FStatusDomain(
        const FStatusDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        CategoryName(From.CategoryName),
        ParentKey(From.ParentKey)
    {

    }

    FStatusDomain::FGetTask::FGetTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FGetStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Model::FStatus>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->GetStatusByUserId(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCategoryName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Idle::Model::FStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FStatusDomain::FGetTask>> FStatusDomain::Get(
        Request::FGetStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FPredictionTask::FPredictionTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FPredictionByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FPredictionTask::FPredictionTask(
        const FPredictionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FPredictionTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Idle::Model::FAcquireAction>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->PredictionByUserId(
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
            
            if (ResultModel->GetStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Idle::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetStatus()->GetCategoryName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Idle::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItems();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FPredictionTask>> FStatusDomain::Prediction(
        Request::FPredictionByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPredictionTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FReceiveTask::FReceiveTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FReceiveByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FReceiveTask::FReceiveTask(
        const FReceiveTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->ReceiveByUserId(
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
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                *Self->UserId,
                false,
                *ResultModel->GetTransactionId(),
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId()
            );
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FReceiveTask>> FStatusDomain::Receive(
        Request::FReceiveByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FIncreaseMaximumIdleMinutesTask::FIncreaseMaximumIdleMinutesTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FIncreaseMaximumIdleMinutesTask::FIncreaseMaximumIdleMinutesTask(
        const FIncreaseMaximumIdleMinutesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FIncreaseMaximumIdleMinutesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->IncreaseMaximumIdleMinutesByUserId(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCategoryName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Idle::Model::FStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FStatusDomain::FIncreaseMaximumIdleMinutesTask>> FStatusDomain::IncreaseMaximumIdleMinutes(
        Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIncreaseMaximumIdleMinutesTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FDecreaseMaximumIdleMinutesTask::FDecreaseMaximumIdleMinutesTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FDecreaseMaximumIdleMinutesByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FDecreaseMaximumIdleMinutesTask::FDecreaseMaximumIdleMinutesTask(
        const FDecreaseMaximumIdleMinutesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FDecreaseMaximumIdleMinutesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->DecreaseMaximumIdleMinutesByUserId(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCategoryName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Idle::Model::FStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FStatusDomain::FDecreaseMaximumIdleMinutesTask>> FStatusDomain::DecreaseMaximumIdleMinutes(
        Request::FDecreaseMaximumIdleMinutesByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDecreaseMaximumIdleMinutesTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FSetMaximumIdleMinutesTask::FSetMaximumIdleMinutesTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FSetMaximumIdleMinutesByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FSetMaximumIdleMinutesTask::FSetMaximumIdleMinutesTask(
        const FSetMaximumIdleMinutesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FSetMaximumIdleMinutesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->SetMaximumIdleMinutesByUserId(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCategoryName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Idle::Model::FStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FStatusDomain::FSetMaximumIdleMinutesTask>> FStatusDomain::SetMaximumIdleMinutes(
        Request::FSetMaximumIdleMinutesByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetMaximumIdleMinutesTask>>(this->AsShared(), Request);
    }

    FString FStatusDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CategoryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            ChildType;
    }

    FString FStatusDomain::CreateCacheKey(
        TOptional<FString> CategoryName
    )
    {
        return FString("") +
            (CategoryName.IsSet() ? *CategoryName : "null");
    }

    FStatusDomain::FModelTask::FModelTask(
        const TSharedPtr<FStatusDomain> Self
    ): Self(Self)
    {

    }

    FStatusDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Model::FStatus>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Idle::Model::FStatus> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Idle::Model::FStatus>(
            Self->ParentKey,
            Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                Self->CategoryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Idle::Request::FGetStatusByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->CategoryName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Idle::Model::FStatus::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "status")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Idle::Model::FStatus>(
                Self->ParentKey,
                Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->CategoryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FModelTask>> FStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStatusDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStatusDomain::Subscribe(
        TFunction<void(Gs2::Idle::Model::FStatusPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Idle::Model::FStatus::TypeName,
            ParentKey,
            Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                CategoryName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Idle::Model::FStatus>(obj));
            }
        );
    }

    void FStatusDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Idle::Model::FStatus::TypeName,
            ParentKey,
            Gs2::Idle::Domain::Model::FStatusDomain::CreateCacheKey(
                CategoryName
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

