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

#include "Grade/Domain/Model/StatusAccessToken.h"
#include "Grade/Domain/Model/Status.h"
#include "Grade/Domain/Model/Namespace.h"
#include "Grade/Domain/Model/GradeModelMaster.h"
#include "Grade/Domain/Model/GradeModel.h"
#include "Grade/Domain/Model/User.h"
#include "Grade/Domain/Model/UserAccessToken.h"
#include "Grade/Domain/Model/Status.h"
#include "Grade/Domain/Model/StatusAccessToken.h"
#include "Grade/Domain/Model/CurrentGradeMaster.h"
#include "Grade/Domain/SpeculativeExecutor/Transaction/MultiplyAcquireActionsByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"
#include "Experience/Domain/Model/Status.h"

namespace Gs2::Grade::Domain::Model
{

    FStatusAccessTokenDomain::FStatusAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Grade::Domain::FGs2GradeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> GradeName,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Grade::FGs2GradeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        GradeName(GradeName),
        PropertyId(PropertyId),
        ParentKey(Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
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
        GradeName(From.GradeName),
        PropertyId(From.PropertyId),
        ParentKey(From.ParentKey)
    {

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
        TSharedPtr<TSharedPtr<Gs2::Grade::Model::FStatus>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGradeName(Self->GradeName)
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
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FGetTask>> FStatusAccessTokenDomain::Get(
        Request::FGetStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStatusAccessTokenDomain::FSubGradeTask::FSubGradeTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FSubGradeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FSubGradeTask::FSubGradeTask(
        const FSubGradeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FSubGradeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->SubGrade(
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
                    Self->UserId(),
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
                    Self->UserId(),
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FSubGradeTask>> FStatusAccessTokenDomain::SubGrade(
        Request::FSubGradeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubGradeTask>>(this->AsShared(), Request);
    }

    FStatusAccessTokenDomain::FApplyRankCapTask::FApplyRankCapTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FApplyRankCapRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FApplyRankCapTask::FApplyRankCapTask(
        const FApplyRankCapTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FApplyRankCapTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->ApplyRankCap(
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
                    Self->UserId(),
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
                    Self->UserId(),
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FApplyRankCapTask>> FStatusAccessTokenDomain::ApplyRankCap(
        Request::FApplyRankCapRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FApplyRankCapTask>>(this->AsShared(), Request);
    }

    FStatusAccessTokenDomain::FVerifyGradeTask::FVerifyGradeTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FVerifyGradeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FVerifyGradeTask::FVerifyGradeTask(
        const FVerifyGradeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FVerifyGradeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->VerifyGrade(
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FVerifyGradeTask>> FStatusAccessTokenDomain::VerifyGrade(
        Request::FVerifyGradeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyGradeTask>>(this->AsShared(), Request);
    }

    FStatusAccessTokenDomain::FVerifyGradeUpMaterialTask::FVerifyGradeUpMaterialTask(
        const TSharedPtr<FStatusAccessTokenDomain>& Self,
        const Request::FVerifyGradeUpMaterialRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FVerifyGradeUpMaterialTask::FVerifyGradeUpMaterialTask(
        const FVerifyGradeUpMaterialTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FVerifyGradeUpMaterialTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGradeName(Self->GradeName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->VerifyGradeUpMaterial(
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FVerifyGradeUpMaterialTask>> FStatusAccessTokenDomain::VerifyGradeUpMaterial(
        Request::FVerifyGradeUpMaterialRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyGradeUpMaterialTask>>(this->AsShared(), Request);
    }

    FString FStatusAccessTokenDomain::CreateCacheParentKey(
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

    FString FStatusAccessTokenDomain::CreateCacheKey(
        TOptional<FString> GradeName,
        TOptional<FString> PropertyId
    )
    {
        return FString("") +
            (GradeName.IsSet() ? *GradeName : "null") + ":" + 
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
                MakeShared<Gs2::Grade::Request::FGetStatusRequest>()
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FModelTask>> FStatusAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStatusAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStatusAccessTokenDomain::Subscribe(
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

    void FStatusAccessTokenDomain::Unsubscribe(
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

