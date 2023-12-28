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

#include "Grade/Domain/Model/Status.h"
#include "Grade/Domain/Model/Namespace.h"
#include "Grade/Domain/Model/GradeModelMaster.h"
#include "Grade/Domain/Model/GradeModel.h"
#include "Grade/Domain/Model/User.h"
#include "Grade/Domain/Model/UserAccessToken.h"
#include "Grade/Domain/Model/Status.h"
#include "Grade/Domain/Model/StatusAccessToken.h"
#include "Grade/Domain/Model/CurrentGradeMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Grade::Domain::Model
{

    FStatusDomain::FStatusDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Grade::Domain::FGs2GradeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> GradeName,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Grade::FGs2GradeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        GradeName(GradeName),
        PropertyId(PropertyId),
        ParentKey(Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
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
        GradeName(From.GradeName),
        PropertyId(From.PropertyId),
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
        TSharedPtr<TSharedPtr<Gs2::Grade::Model::FStatus>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
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
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
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

    FStatusDomain::FAddGradeTask::FAddGradeTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FAddGradeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FAddGradeTask::FAddGradeTask(
        const FAddGradeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FAddGradeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->AddGradeByUserId(
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
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetExperienceStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetExperienceStatus()->GetExperienceName(),
                    ResultModel->GetExperienceStatus()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetExperienceStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->ExperienceNamespaceName = *ResultModel->GetExperienceNamespaceName();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FAddGradeTask>> FStatusDomain::AddGrade(
        Request::FAddGradeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddGradeTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FSubGradeTask::FSubGradeTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FSubGradeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FSubGradeTask::FSubGradeTask(
        const FSubGradeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FSubGradeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->SubGradeByUserId(
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
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetExperienceStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetExperienceStatus()->GetExperienceName(),
                    ResultModel->GetExperienceStatus()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetExperienceStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->ExperienceNamespaceName = *ResultModel->GetExperienceNamespaceName();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FSubGradeTask>> FStatusDomain::SubGrade(
        Request::FSubGradeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubGradeTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FSetGradeTask::FSetGradeTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FSetGradeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FSetGradeTask::FSetGradeTask(
        const FSetGradeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FSetGradeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->SetGradeByUserId(
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
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetExperienceStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetExperienceStatus()->GetExperienceName(),
                    ResultModel->GetExperienceStatus()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetExperienceStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->ExperienceNamespaceName = *ResultModel->GetExperienceNamespaceName();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FSetGradeTask>> FStatusDomain::SetGrade(
        Request::FSetGradeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetGradeTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FApplyRankCapTask::FApplyRankCapTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FApplyRankCapByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FApplyRankCapTask::FApplyRankCapTask(
        const FApplyRankCapTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FApplyRankCapTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->ApplyRankCapByUserId(
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
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetExperienceStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetExperienceStatus()->GetExperienceName(),
                    ResultModel->GetExperienceStatus()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetExperienceStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->ExperienceNamespaceName = *ResultModel->GetExperienceNamespaceName();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FApplyRankCapTask>> FStatusDomain::ApplyRankCap(
        Request::FApplyRankCapByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FApplyRankCapTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FDeleteStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->DeleteStatusByUserId(
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
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Delete(Gs2::Grade::Model::FStatus::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FDeleteTask>> FStatusDomain::Delete(
        Request::FDeleteStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FVerifyGradeTask::FVerifyGradeTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FVerifyGradeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FVerifyGradeTask::FVerifyGradeTask(
        const FVerifyGradeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FVerifyGradeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->VerifyGradeByUserId(
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
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FVerifyGradeTask>> FStatusDomain::VerifyGrade(
        Request::FVerifyGradeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyGradeTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FVerifyGradeUpMaterialTask::FVerifyGradeUpMaterialTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FVerifyGradeUpMaterialByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FVerifyGradeUpMaterialTask::FVerifyGradeUpMaterialTask(
        const FVerifyGradeUpMaterialTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FVerifyGradeUpMaterialTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->VerifyGradeUpMaterialByUserId(
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
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FVerifyGradeUpMaterialTask>> FStatusDomain::VerifyGradeUpMaterial(
        Request::FVerifyGradeUpMaterialByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyGradeUpMaterialTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FMultiplyAcquireActionsTask::FMultiplyAcquireActionsTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FMultiplyAcquireActionsByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FMultiplyAcquireActionsTask::FMultiplyAcquireActionsTask(
        const FMultiplyAcquireActionsTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FMultiplyAcquireActionsTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->MultiplyAcquireActionsByUserId(
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

    TSharedPtr<FAsyncTask<FStatusDomain::FMultiplyAcquireActionsTask>> FStatusDomain::MultiplyAcquireActions(
        Request::FMultiplyAcquireActionsByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FMultiplyAcquireActionsTask>>(this->AsShared(), Request);
    }

    FString FStatusDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> GradeName,
        TOptional<FString> PropertyId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (GradeName.IsSet() ? *GradeName : "null") + ":" +
            (PropertyId.IsSet() ? *PropertyId : "null") + ":" +
            ChildType;
    }

    FString FStatusDomain::CreateCacheKey(
        TOptional<FString> GradeName,
        TOptional<FString> PropertyId
    )
    {
        return FString("") +
            (GradeName.IsSet() ? *GradeName : "null") + ":" + 
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
        TSharedPtr<TSharedPtr<Gs2::Grade::Model::FStatus>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Grade::Model::FStatus> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Grade::Model::FStatus>(
            Self->ParentKey,
            Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                Self->GradeName,
                Self->PropertyId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Grade::Request::FGetStatusByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->GradeName,
                    Self->PropertyId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
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
            Self->Gs2->Cache->TryGet<Gs2::Grade::Model::FStatus>(
                Self->ParentKey,
                Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->GradeName,
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
        TFunction<void(Gs2::Grade::Model::FStatusPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Grade::Model::FStatus::TypeName,
            ParentKey,
            Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                GradeName,
                PropertyId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Grade::Model::FStatus>(obj));
            }
        );
    }

    void FStatusDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Grade::Model::FStatus::TypeName,
            ParentKey,
            Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                GradeName,
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

