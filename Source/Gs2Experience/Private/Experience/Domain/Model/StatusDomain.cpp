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

#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/Namespace.h"
#include "Experience/Domain/Model/ExperienceModelMaster.h"
#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Domain/Model/ThresholdMaster.h"
#include "Experience/Domain/Model/CurrentExperienceMaster.h"
#include "Experience/Domain/Model/User.h"
#include "Experience/Domain/Model/UserAccessToken.h"
#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/StatusAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Experience::Domain::Model
{

    FStatusDomain::FStatusDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> ExperienceName,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Experience::FGs2ExperienceRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ExperienceName(ExperienceName),
        PropertyId(PropertyId),
        ParentKey(Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Status"
        ))
    {
    }

    FStatusDomain::FStatusDomain(
        const FStatusDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FStatusDomain::FGetTask::FGetTask(
        const TSharedPtr<FStatusDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FStatus>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithExperienceName(Self->ExperienceName)
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetExperienceName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Experience::Model::FStatus>(
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

    FStatusDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const TSharedPtr<FStatusDomain> Self,
        const Request::FGetStatusWithSignatureByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const FGetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FGetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithExperienceName(Self->ExperienceName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetStatusWithSignatureByUserId(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetExperienceName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Experience::Model::FStatus>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        Domain->Body = *ResultModel->GetBody();
        Domain->Signature = *ResultModel->GetSignature();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FGetWithSignatureTask>> FStatusDomain::GetWithSignature(
        Request::FGetStatusWithSignatureByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetWithSignatureTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FAddExperienceTask::FAddExperienceTask(
        const TSharedPtr<FStatusDomain> Self,
        const Request::FAddExperienceByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FAddExperienceTask::FAddExperienceTask(
        const FAddExperienceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FAddExperienceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithExperienceName(Self->ExperienceName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->AddExperienceByUserId(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetExperienceName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Experience::Model::FStatus>(
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

    TSharedPtr<FAsyncTask<FStatusDomain::FAddExperienceTask>> FStatusDomain::AddExperience(
        Request::FAddExperienceByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddExperienceTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FSetExperienceTask::FSetExperienceTask(
        const TSharedPtr<FStatusDomain> Self,
        const Request::FSetExperienceByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FSetExperienceTask::FSetExperienceTask(
        const FSetExperienceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FSetExperienceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithExperienceName(Self->ExperienceName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->SetExperienceByUserId(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetExperienceName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Experience::Model::FStatus>(
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

    TSharedPtr<FAsyncTask<FStatusDomain::FSetExperienceTask>> FStatusDomain::SetExperience(
        Request::FSetExperienceByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetExperienceTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FAddRankCapTask::FAddRankCapTask(
        const TSharedPtr<FStatusDomain> Self,
        const Request::FAddRankCapByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FAddRankCapTask::FAddRankCapTask(
        const FAddRankCapTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FAddRankCapTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithExperienceName(Self->ExperienceName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->AddRankCapByUserId(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetExperienceName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Experience::Model::FStatus>(
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

    TSharedPtr<FAsyncTask<FStatusDomain::FAddRankCapTask>> FStatusDomain::AddRankCap(
        Request::FAddRankCapByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddRankCapTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FSetRankCapTask::FSetRankCapTask(
        const TSharedPtr<FStatusDomain> Self,
        const Request::FSetRankCapByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FSetRankCapTask::FSetRankCapTask(
        const FSetRankCapTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FSetRankCapTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithExperienceName(Self->ExperienceName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->SetRankCapByUserId(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetExperienceName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Experience::Model::FStatus>(
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

    TSharedPtr<FAsyncTask<FStatusDomain::FSetRankCapTask>> FStatusDomain::SetRankCap(
        Request::FSetRankCapByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetRankCapTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStatusDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithExperienceName(Self->ExperienceName)
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetExperienceName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Delete<Gs2::Experience::Model::FStatus>(ParentKey, Key);
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

    FString FStatusDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> ExperienceName,
        TOptional<FString> PropertyId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (ExperienceName.IsSet() ? *ExperienceName : "null") + ":" +
            (PropertyId.IsSet() ? *PropertyId : "null") + ":" +
            ChildType;
    }

    FString FStatusDomain::CreateCacheKey(
        TOptional<FString> ExperienceName,
        TOptional<FString> PropertyId
    )
    {
        return FString() +
            (ExperienceName.IsSet() ? *ExperienceName : "null") + ":" + 
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
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FStatus>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Experience::Model::FStatus>(
            Self->ParentKey,
            Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                Self->ExperienceName,
                Self->PropertyId
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Experience::Request::FGetStatusByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "status")
                    {
                        Self->Cache->Delete<Gs2::Experience::Model::FStatus>(
                            Self->ParentKey,
                            Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                                Self->ExperienceName,
                                Self->PropertyId
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Experience::Model::FStatus>(
                Self->ParentKey,
                Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->ExperienceName,
                    Self->PropertyId
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FModelTask>> FStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStatusDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

