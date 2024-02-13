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

#include "SkillTree/Domain/Model/StatusAccessToken.h"
#include "SkillTree/Domain/Model/Status.h"
#include "SkillTree/Domain/Model/Namespace.h"
#include "SkillTree/Domain/Model/NodeModel.h"
#include "SkillTree/Domain/Model/NodeModelMaster.h"
#include "SkillTree/Domain/Model/Status.h"
#include "SkillTree/Domain/Model/StatusAccessToken.h"
#include "SkillTree/Domain/Model/CurrentTreeMaster.h"
#include "SkillTree/Domain/Model/User.h"
#include "SkillTree/Domain/Model/UserAccessToken.h"
#include "SkillTree/Domain/SpeculativeExecutor/Transaction/ReleaseByUserIdSpeculativeExecutor.h"
#include "SkillTree/Domain/SpeculativeExecutor/Transaction/RestrainByUserIdSpeculativeExecutor.h"
#include "SkillTree/Domain/SpeculativeExecutor/Transaction/ResetByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::SkillTree::Domain::Model
{

    FStatusAccessTokenDomain::FStatusAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SkillTree::FGs2SkillTreeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        PropertyId(PropertyId),
        ParentKey(Gs2::SkillTree::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Status"
        ))
    {
    }

    FStatusAccessTokenDomain::FStatusAccessTokenDomain(
        const FStatusAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        PropertyId(From.PropertyId),
        ParentKey(From.ParentKey)
    {

    }

    FStatusAccessTokenDomain::FReleaseTask::FReleaseTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FReleaseRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FStatusAccessTokenDomain::FReleaseTask::FReleaseTask(
        const FReleaseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FReleaseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithPropertyId(Self->PropertyId);

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FReleaseByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FReleaseByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->Release(
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
                const auto ParentKey = Gs2::SkillTree::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Status"
                );
                const auto Key = Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SkillTree::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FReleaseTask>> FStatusAccessTokenDomain::Release(
        Request::FReleaseRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReleaseTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FStatusAccessTokenDomain::FRestrainTask::FRestrainTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FRestrainRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FStatusAccessTokenDomain::FRestrainTask::FRestrainTask(
        const FRestrainTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FRestrainTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithPropertyId(Self->PropertyId);

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FRestrainByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FRestrainByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->Restrain(
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
                const auto ParentKey = Gs2::SkillTree::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Status"
                );
                const auto Key = Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SkillTree::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FRestrainTask>> FStatusAccessTokenDomain::Restrain(
        Request::FRestrainRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRestrainTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FStatusAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FGetStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FStatus>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetStatus(
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
                const auto ParentKey = Gs2::SkillTree::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Status"
                );
                const auto Key = Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SkillTree::Model::FStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FGetTask>> FStatusAccessTokenDomain::Get(
        Request::FGetStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStatusAccessTokenDomain::FResetTask::FResetTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FResetRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FStatusAccessTokenDomain::FResetTask::FResetTask(
        const FResetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FResetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithPropertyId(Self->PropertyId);

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FResetByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FResetByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->Reset(
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
                const auto ParentKey = Gs2::SkillTree::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Status"
                );
                const auto Key = Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SkillTree::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FResetTask>> FStatusAccessTokenDomain::Reset(
        Request::FResetRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FResetTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FString FStatusAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> PropertyId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (PropertyId.IsSet() ? *PropertyId : "null") + ":" +
            ChildType;
    }

    FString FStatusAccessTokenDomain::CreateCacheKey(
        TOptional<FString> PropertyId
    )
    {
        return FString("") +
            (PropertyId.IsSet() ? *PropertyId : "null");
    }

    FStatusAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FStatusAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FStatusAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FStatus>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::SkillTree::Model::FStatus> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::SkillTree::Model::FStatus>(
            Self->ParentKey,
            Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                Self->PropertyId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SkillTree::Request::FGetStatusRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->PropertyId
                );
                Self->Gs2->Cache->Put(
                    Gs2::SkillTree::Model::FStatus::TypeName,
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
            Self->Gs2->Cache->TryGet<Gs2::SkillTree::Model::FStatus>(
                Self->ParentKey,
                Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->PropertyId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FModelTask>> FStatusAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStatusAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStatusAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::SkillTree::Model::FStatusPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::SkillTree::Model::FStatus::TypeName,
            ParentKey,
            Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                PropertyId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SkillTree::Model::FStatus>(obj));
            }
        );
    }

    void FStatusAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::SkillTree::Model::FStatus::TypeName,
            ParentKey,
            Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                PropertyId
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

