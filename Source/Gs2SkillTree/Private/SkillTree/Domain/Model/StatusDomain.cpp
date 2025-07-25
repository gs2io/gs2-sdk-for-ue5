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

#include "SkillTree/Domain/Model/Status.h"
#include "SkillTree/Domain/Model/Namespace.h"
#include "SkillTree/Domain/Model/NodeModel.h"
#include "SkillTree/Domain/Model/NodeModelMaster.h"
#include "SkillTree/Domain/Model/Status.h"
#include "SkillTree/Domain/Model/StatusAccessToken.h"
#include "SkillTree/Domain/Model/CurrentTreeMaster.h"
#include "SkillTree/Domain/Model/User.h"
#include "SkillTree/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::SkillTree::Domain::Model
{

    FStatusDomain::FStatusDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SkillTree::FGs2SkillTreeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        PropertyId(PropertyId),
        ParentKey(Gs2::SkillTree::Domain::Model::FUserDomain::CreateCacheParentKey(
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
        PropertyId(From.PropertyId),
        ParentKey(From.ParentKey)
    {

    }

    FStatusDomain::FMarkReleaseTask::FMarkReleaseTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FMarkReleaseByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FMarkReleaseTask::FMarkReleaseTask(
        const FMarkReleaseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FMarkReleaseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->MarkReleaseByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FMarkReleaseTask>> FStatusDomain::MarkRelease(
        Request::FMarkReleaseByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FMarkReleaseTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FReleaseTask::FReleaseTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FReleaseByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FReleaseTask::FReleaseTask(
        const FReleaseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FReleaseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->ReleaseByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            *ResultModel->GetTransactionId(),
            *ResultModel->GetStampSheet(),
            *ResultModel->GetStampSheetEncryptionKeyId(),
            *ResultModel->GetAtomicCommit(),
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FReleaseTask>> FStatusDomain::Release(
        Request::FReleaseByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReleaseTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FMarkRestrainTask::FMarkRestrainTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FMarkRestrainByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FMarkRestrainTask::FMarkRestrainTask(
        const FMarkRestrainTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FMarkRestrainTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->MarkRestrainByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FMarkRestrainTask>> FStatusDomain::MarkRestrain(
        Request::FMarkRestrainByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FMarkRestrainTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FRestrainTask::FRestrainTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FRestrainByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FRestrainTask::FRestrainTask(
        const FRestrainTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FRestrainTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->RestrainByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            *ResultModel->GetTransactionId(),
            *ResultModel->GetStampSheet(),
            *ResultModel->GetStampSheetEncryptionKeyId(),
            *ResultModel->GetAtomicCommit(),
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FRestrainTask>> FStatusDomain::Restrain(
        Request::FRestrainByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRestrainTask>>(this->AsShared(), Request);
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
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FStatus>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetStatusByUserId(
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

    TSharedPtr<FAsyncTask<FStatusDomain::FGetTask>> FStatusDomain::Get(
        Request::FGetStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FResetTask::FResetTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FResetByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FResetTask::FResetTask(
        const FResetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FResetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->ResetByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            *ResultModel->GetTransactionId(),
            *ResultModel->GetStampSheet(),
            *ResultModel->GetStampSheetEncryptionKeyId(),
            *ResultModel->GetAtomicCommit(),
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FResetTask>> FStatusDomain::Reset(
        Request::FResetByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FResetTask>>(this->AsShared(), Request);
    }

    FString FStatusDomain::CreateCacheParentKey(
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

    FString FStatusDomain::CreateCacheKey(
        TOptional<FString> PropertyId
    )
    {
        return FString("") +
            (PropertyId.IsSet() ? *PropertyId : "null");
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
                MakeShared<Gs2::SkillTree::Request::FGetStatusByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FStatusDomain::FModelTask>> FStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStatusDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStatusDomain::Subscribe(
        TFunction<void(Gs2::SkillTree::Model::FStatusPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::SkillTree::Model::FStatus::TypeName,
            ParentKey,
            Gs2::SkillTree::Domain::Model::FStatusDomain::CreateCacheKey(
                PropertyId
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SkillTree::Model::FStatus>(obj));
            }
        );
    }

    void FStatusDomain::Unsubscribe(
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

