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

#include "Quest/Domain/Model/QuestModelMaster.h"
#include "Quest/Domain/Model/Namespace.h"
#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/QuestModelMaster.h"
#include "Quest/Domain/Model/CurrentQuestMaster.h"
#include "Quest/Domain/Model/Progress.h"
#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Domain/Model/CompletedQuestList.h"
#include "Quest/Domain/Model/CompletedQuestListAccessToken.h"
#include "Quest/Domain/Model/QuestGroupModel.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/User.h"
#include "Quest/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FQuestModelMasterDomain::FQuestModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> QuestGroupName,
        const TOptional<FString> QuestName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Session)),
        NamespaceName(NamespaceName),
        QuestGroupName(QuestGroupName),
        QuestName(QuestName),
        ParentKey(Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheParentKey(
            NamespaceName,
            QuestGroupName,
            "QuestModelMaster"
        ))
    {
    }

    FQuestModelMasterDomain::FQuestModelMasterDomain(
        const FQuestModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FQuestModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FQuestModelMasterDomain> Self,
        const Request::FGetQuestModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithQuestName(Self->QuestName);
        const auto Future = Self->Client->GetQuestModelMaster(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->QuestGroupName,
                    "QuestModelMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Quest::Model::FQuestModelMaster>(
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

    TSharedPtr<FAsyncTask<FQuestModelMasterDomain::FGetTask>> FQuestModelMasterDomain::Get(
        Request::FGetQuestModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FQuestModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FQuestModelMasterDomain> Self,
        const Request::FUpdateQuestModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithQuestName(Self->QuestName);
        const auto Future = Self->Client->UpdateQuestModelMaster(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->QuestGroupName,
                    "QuestModelMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Quest::Model::FQuestModelMaster>(
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

    TSharedPtr<FAsyncTask<FQuestModelMasterDomain::FUpdateTask>> FQuestModelMasterDomain::Update(
        Request::FUpdateQuestModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FQuestModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FQuestModelMasterDomain> Self,
        const Request::FDeleteQuestModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithQuestName(Self->QuestName);
        const auto Future = Self->Client->DeleteQuestModelMaster(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->QuestGroupName,
                    "QuestModelMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete<Gs2::Quest::Model::FQuestModelMaster>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestModelMasterDomain::FDeleteTask>> FQuestModelMasterDomain::Delete(
        Request::FDeleteQuestModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FQuestModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> QuestGroupName,
        TOptional<FString> QuestName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null") + ":" +
            (QuestName.IsSet() ? *QuestName : "null") + ":" +
            ChildType;
    }

    FString FQuestModelMasterDomain::CreateCacheKey(
        TOptional<FString> QuestName
    )
    {
        return FString() +
            (QuestName.IsSet() ? *QuestName : "null");
    }

    FQuestModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FQuestModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FQuestModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Quest::Model::FQuestModelMaster>(
            Self->ParentKey,
            Gs2::Quest::Domain::Model::FQuestModelMasterDomain::CreateCacheKey(
                Self->QuestName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Quest::Request::FGetQuestModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "questModelMaster")
                    {
                        Self->Cache->Delete<Gs2::Quest::Model::FQuestModelMaster>(
                            Self->ParentKey,
                            Gs2::Quest::Domain::Model::FQuestModelMasterDomain::CreateCacheKey(
                                Self->QuestName
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
            Value = Self->Cache->Get<Gs2::Quest::Model::FQuestModelMaster>(
                Self->ParentKey,
                Gs2::Quest::Domain::Model::FQuestModelMasterDomain::CreateCacheKey(
                    Self->QuestName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestModelMasterDomain::FModelTask>> FQuestModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FQuestModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

