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

#include "SkillTree/Domain/SpeculativeExecutor/Transaction/ReleaseByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::SkillTree::Domain::Transaction::SpeculativeExecutor
{
    FString FReleaseByUserIdSpeculativeExecutor::Action() {
        return "Gs2SkillTree:ReleaseByUserId";
    }

    FReleaseByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SkillTree::Request::FReleaseByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FReleaseByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReleaseByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result)
    {
        for (auto NodeModelName : *Request->GetNodeModelNames())
        {
            const auto Future = Domain->SkillTree->Namespace(
                    Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : ""
                )->NodeModel(
                    NodeModelName
                )->Model();
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            const auto Item = Future->GetTask().Result();

            Service->OnIssueTransaction.Broadcast(
                MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
                    AccessToken,
                    Item->GetReleaseConsumeActions(),
                    [NodeModelName, this]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
                        Arr->Add(
                            MakeShared<Gs2::Core::Model::FAcquireAction>()
                                ->WithAction(TOptional<FString>("Gs2SkillTree:MarkReleaseByUserId"))
                                ->WithRequest(TOptional<FString>(
                                    [NodeModelName, this]
                                    {
                                        FString Body("");
                                        const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
                                        FJsonSerializer::Serialize(
                                        MakeShared<Gs2::SkillTree::Request::FMarkReleaseByUserIdRequest>()
                                                ->WithNamespaceName(Request->GetNamespaceName())
                                                ->WithUserId(AccessToken->GetUserId())
                                                ->WithPropertyId(Request->GetPropertyId())
                                                ->WithNodeModelNames(
                                                    [NodeModelName]
                                                    {
                                                        auto Arr = MakeShared<TArray<FString>>();
                                                        Arr->Add(NodeModelName);
                                                        return Arr;
                                                    }()
                                                )
                                                ->ToJson().ToSharedRef(), Writer);
                                        return Body;
                                    }()
                                ))
                        );
                        return Arr;
                    }(),
                    1.0
                )
            );
        }

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReleaseByUserIdSpeculativeExecutor::FCommitTask>> FReleaseByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SkillTree::Request::FReleaseByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
